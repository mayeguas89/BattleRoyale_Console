#pragma once

#include "ability.h"
#include "armor.h"
#include "classes/class.h"
#include "death_saving_throw.h"
#include "dice.h"
#include "health.h"
#include "helpers.h"
#include "races/race.h"
#include "spell.h"
#include "weapon.h"

#include <memory>
#include <optional>

class Character
{
public:
  enum class State
  {
    Alive,
    Death,
    Unconscious,
    Stable,
  };

  Character(Abilities abilities, std::unique_ptr<Race> race, std::unique_ptr<Class> p_class):
    abilities_{abilities},
    race_{std::move(race)},
    class_{std::move(p_class)},
    state_{State::Alive},
    health_{class_->GetHitDice() + GetAbilityModifier(Ability::Type::Constitution)}
  {}

  std::optional<Ability> GetAbility(Ability::Type type)
  {
    if (auto it = abilities_.map.find(type); it != abilities_.map.end())
    {
      return it->second;
    }
    return std::nullopt;
  }

  int GetDifficultyClass()
  {
    auto ability = class_->GetSpellCastingAbility();
    return 8 + GetAbilityModifier(ability);
  }

  int GetArmorClass()
  {
    auto dexterity_modifier = GetAbilityModifier(Ability::Type::Dexterity);

    return helpers::GetArmorClass(dexterity_modifier, wear_armor_, shield_);
  }

  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipWearAmor(std::shared_ptr<WearArmor> wear_armor)
  {
    auto dexterity_modifier = GetAbilityModifier(Ability::Type::Dexterity);

    auto previous_ac = helpers::GetArmorClass(dexterity_modifier, wear_armor_, shield_);
    auto new_ac = helpers::GetArmorClass(dexterity_modifier, wear_armor, shield_);
    if (new_ac > previous_ac)
      wear_armor_ = wear_armor;
  }

  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipShield(std::shared_ptr<Shield> shield)
  {
    int previous_ac =
      helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
    int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield);
    if (new_ac > previous_ac)
      shield_ = shield;
  }

  void EquipWeapon(std::shared_ptr<Weapon> weapon)
  {
    weapon_ = weapon;
  }

  int GetAttackModifier()
  {
    if (!weapon_)
      return 0;
    return GetAbilityModifier(weapon_->GetAttackAbilityModifier());
  }

  int RollDamage()
  {
    // When attacking with a weapon, you add your ability modifier
    // A spell tells you which dice to roll for damage and whether to add any modifier

    // Se pueden añadir diferentes tipos de daños segun arma/hechizo usado

    // If a creature or an object has resistance to a damage
    // type, damage o f that type is halved against it. If a
    // creature or an object has vulnerability to a damage
    // type, damage o f that type is doubled against it.

    // magical methods such as a cure wounds spell or
    // a potion of healing can remove damage in an instant.return 0;
    auto damage = GetAttackModifier();
    if (weapon_)
      damage += weapon_->GetDamage();

    return damage;
  }

  // Massive damage can kill you instantly. When damage
  // reduces you to 0 hit points and there is damage
  // remaining, you die if the remaining damage equals
  // or exceeds your hit point maximum.
  void ReceiveDamage(int damage)
  {
    int remaning_damage = health_.TakeDamage(damage);

    int current_life = health_.GetCurrent();

    if (current_life == 0)
    {
      if (remaning_damage == health_.GetHitPoints())
      {
        state_ = State::Death;
      }
      else
      {
        // This unconsciousness ends if you regain any hit points
        if (state_ == State::Unconscious)
          death_saving_throw_.AddFailure();
        else
          state_ = State::Unconscious;
      }
    }
  }

  // Se puede tener más vida que el hit_die?
  void Heal(int amount)
  {
    health_.Heal(amount);
  }

  void TakeAction()
  {
    if (state_ == State::Unconscious)
    {
      auto [succes, failure, heal] = death_saving_throw_();
      if (heal)
        health_.Heal(1);
      if (succes == 3)
      {
        state_ = State::Stable;
        death_saving_throw_.Restart();
      }
      else if (failure == 3)
      {
        state_ = State::Death;
      }
    }

    if (state_ == State::Death)
      return;
  }

  int SavingThrows(AbilityType ability_type)
  {
    auto roll = SingletonDice::Get().Roll(20);
    if (class_->HasSavingThrowModifier(ability_type))
      roll += GetAbilityModifier(ability_type);
    return roll;
  }

protected:
  Abilities abilities_;

  std::shared_ptr<WearArmor> wear_armor_;
  std::shared_ptr<Shield> shield_;

  std::unique_ptr<Race> race_;
  std::unique_ptr<Class> class_;

  int number_of_spell_slots_ = 0;

  Health health_;

  DeathSavingThrow death_saving_throw_;

  State state_;

  std::shared_ptr<Weapon> weapon_;

  std::vector<Spell> spells_;
  std::vector<Cantrip> cantrips_;

private:
  int GetAbilityModifier(Ability::Type type)
  {
    if (auto ability = GetAbility(type); ability.has_value())
      return ability->GetModifier();
    return 0;
  }
};