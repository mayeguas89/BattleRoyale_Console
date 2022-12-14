#pragma once

#include "ability.h"
#include "armor.h"
#include "class.h"
#include "death_saving_throw.h"
#include "dice.h"
#include "health.h"
#include "helpers.h"
#include "race.h"
#include "weapon.h"

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
    health_{class_->GetHitDie()}
  {}

  std::optional<Ability> GetAbility(Ability::Type type)
  {
    if (auto it = abilities_.map.find(type); it != abilities_.map.end())
    {
      return it->second;
    }
    return std::nullopt;
  }

  int GetArmorClass()
  {
    return helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
  }

  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipWearAmor(const WearArmor& wear_armor)
  {
    int previous_ac =
      helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
    int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor, shield_);
    if (new_ac > previous_ac)
      wear_armor_ = wear_armor;
  }
  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipShield(const Shield& shield)
  {
    int previous_ac =
      helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
    int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield);
    if (new_ac > previous_ac)
      shield_ = shield;
  }

  void EquipWeapon(const Weapon& weapon)
  {
    weapon_ = weapon;
  }

  int GetAttackModifier()
  {
    return helpers::GetAttackModifier(weapon_, abilities_);
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
    if(weapon_) return weapon_->GetDamage();
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
      if (remaning_damage == health_.GetHitdie())
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

protected:
  Abilities abilities_;

  std::optional<WearArmor> wear_armor_;
  std::optional<Shield> shield_;

  std::unique_ptr<Race> race_;
  std::unique_ptr<Class> class_;

  int number_of_spell_slots_ = 0;

  Health health_;

  DeathSavingThrow death_saving_throw_;

  State state_;

  std::optional<Weapon> weapon_;
};