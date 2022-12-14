#pragma once

#include "ability.h"

#include <vector>

using AbilityType = Ability::Type;

class Class
{
public:
  enum class Type
  {
    Barbarian,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard
  };

  Class(Abilities& abilities, int hit_dice, int hit_die_per_level) {}
  virtual ~Class() = default;
  virtual AbilityType GetSpellCastingAbility()
  {
    return AbilityType::None;
  }

  int GetHitDice()
  {
    return hit_dice_;
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
};