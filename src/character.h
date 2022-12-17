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

#include <fmt/format.h>

#include <memory>
#include <optional>

enum class TurnActionType;

class Character
{
public:
  enum class State
  {
    Alive = 0,
    Death,
    Unconscious,
    Stable,
    None
  };
  virtual ~Character() = default;
  Character(Abilities abilities, std::unique_ptr<Race> race, std::unique_ptr<Class> p_class):
    abilities_{abilities},
    race_{std::move(race)},
    class_{std::move(p_class)},
    state_{State::Alive},
    health_{class_->GetHitDice() + GetAbilityModifier(Ability::Type::Constitution)},
    spell_slots_{2},
    level_{1},
    status_effect_{StatusEffect::None}
  {}

  Character(const Character& other)
  {
    race_ = std::make_unique<Race>(*other.race_);
    class_ = std::make_unique<Class>(*other.class_);
    if (other.wear_armor_)
      wear_armor_ = other.wear_armor_;
    if (other.shield_)
      shield_ = other.shield_;
    if (other.weapon_)
      weapon_ = other.weapon_;

    abilities_ = other.abilities_;

    spell_slots_ = other.spell_slots_;

    health_ = other.health_;

    death_saving_throw_ = other.death_saving_throw_;

    state_ = other.state_;

    spells_ = other.spells_;
    // cantrips_ = other.cantrips_;
  }

  Character& operator=(const Character& other)
  {
    race_ = std::make_unique<Race>(*other.race_);
    class_ = std::make_unique<Class>(*other.class_);
    if (other.wear_armor_)
      wear_armor_ = other.wear_armor_;
    if (other.shield_)
      shield_ = other.shield_;
    if (other.weapon_)
      weapon_ = other.weapon_;

    abilities_ = other.abilities_;

    spell_slots_ = other.spell_slots_;

    health_ = other.health_;

    death_saving_throw_ = other.death_saving_throw_;

    state_ = other.state_;

    spells_ = other.spells_;
    // cantrips_ = other.cantrips_;
    return *this;
  }

  std::optional<Ability> GetAbility(Ability::Type type);

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
  void EquipWearAmor(std::shared_ptr<WearArmor> wear_armor);

  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipShield(std::shared_ptr<Shield> shield);

  void EquipWeapon(std::shared_ptr<Weapon> weapon);

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
  void ReceiveDamage(int damage);

  // Se puede tener más vida que el hit_die?
  void Heal(int amount)
  {
    health_.Heal(amount);
  }

  TurnActionType DoAction();

  int SavingThrows(AbilityType ability_type)
  {
    auto roll = SingletonDice::Get().Roll(20);
    if (class_->HasSavingThrowModifier(ability_type))
      roll += GetAbilityModifier(ability_type);
    return roll;
  }

  bool CanThrowSpels()
  {
    return class_->GetSpellCastingAbility() != AbilityType::None;
  }

  void EquipSpell(std::shared_ptr<Spell> spell)
  {
    if (spells_.size() < spell_slots_)
      spells_.push_back(spell);
  }

  void LevelUp()
  {
    spell_slots_++;
    level_++;
  }

  int GetNumberOfSpellsSlots()
  {
    return spell_slots_;
  }

  Weapon* GetWeapon()
  {
    if (weapon_)
      return weapon_.get();
    return nullptr;
  }

  WearArmor* GetArmor()
  {
    if (wear_armor_)
      return wear_armor_.get();
    return nullptr;
  }

  Shield* GetShield()
  {
    if (shield_)
      return shield_.get();
    return nullptr;
  }

  bool IsAlive()
  {
    return state_ != State::Death;
  }

  Spell* GetSpell()
  {
    auto index = SingletonDice::Get().Roll(spell_slots_) - 1;
    return spells_.at(index).get();
  }

  void PrintStats();

  friend std::ostream& operator<<(std::ostream& os, const Character& c);

protected:
  Abilities abilities_;

  std::shared_ptr<WearArmor> wear_armor_;
  std::shared_ptr<Shield> shield_;
  std::shared_ptr<Weapon> weapon_;

  std::unique_ptr<Race> race_;
  std::unique_ptr<Class> class_;

  Health health_;

  DeathSavingThrow death_saving_throw_;

  State state_;
  StatusEffect status_effect_;

  int level_;
  int spell_slots_;
  std::vector<std::shared_ptr<Spell>> spells_;
  // std::vector<Cantrip> cantrips_;

private:
  int GetAbilityModifier(Ability::Type type)
  {
    if (auto ability = GetAbility(type); ability.has_value())
      return ability->GetModifier();
    return 0;
  }
};

inline std::string StateToString(Character::State state)
{
  using State = Character::State;
  switch (state)
  {
    case State::Alive:
      return "Alive";
    case State::Death:
      return "Death";
    case State::Stable:
      return "Stable";
    case State::Unconscious:
      return "Unconscious";
  }
  return "None";
}

inline std::ostream& operator<<(std::ostream& os, const Character& c)
{
  if (c.shield_)
    os << fmt::format("Shield: {}\n", *c.shield_);
  if (c.weapon_)
    os << fmt::format("Weapon: {}\n", *c.weapon_);
  if (c.wear_armor_)
    os << fmt::format("WearArmor: {}\n", *c.wear_armor_);
  return os;
}

template<>
struct fmt::formatter<Character>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const Character& c, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{Weapon: {}, Shield: {}, WearArmor: {}}}",
                            fmt::ptr(c.GetWeapon()),
                            fmt::ptr(c.GetShield()),
                            fmt::ptr(c.GetArmor()));

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};