#pragma once

#include "ability.h"

#include <vector>

using AbilityType = Ability::Type;

class Class
{
public:
  enum class Type
  {
    Barbarian = 0,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard,
    None
  };

  Class(Abilities& abilities, int hit_dice, int hit_die_per_level)
  {
    instances_counter_++;
  }

  virtual ~Class() = default;

  virtual AbilityType GetSpellCastingAbility()
  {
    return AbilityType::None;
  }

  int GetHitDice()
  {
    return hit_dice_;
  }

  int GetInstancesCounter()
  {
    return instances_counter_;
  }

  bool HasSavingThrowModifier(AbilityType ability_type)
  {
    return std::find(saving_throw.begin(), saving_throw.end(), ability_type) != saving_throw.end();
  }

protected:
  int hit_dice_;
  int hit_die_per_level_;
  std::vector<AbilityType> primary_hability_;
  std::vector<AbilityType> saving_throw;
  inline static int instances_counter_ = 0;
};

inline std::string TypeToString(const Class::Type& type)
{
  using Type = Class::Type;
  switch (type)
  {
    case Type::Barbarian:
      return "Barbarian";
    case Type::Bard:
      return "Bard";
    case Type::Cleric:
      return "Cleric";
    case Type::Druid:
      return "Druid";
    case Type::Fighter:
      return "Fighter";
    case Type::Ranger:
      return "Ranger";
    case Type::Rogue:
      return "Rogue";
    case Type::Sorcerer:
      return "Sorcerer";
    case Type::Warlock:
      return "Warlock";
    case Type::Wizard:
      return "Wizard";
    default:
      return "INVALID";
  }
}