#pragma once

#include "class.h"

class Warlock: public Class
{
public:
  enum class Type
  {
    TheFiendWarlock,
    TheGreatOldOneWarlock
  };
  struct Visitor
  {
    std::optional<Type> operator()(Type type) const
    {
      return type;
    }
    template<typename T>
    std::optional<Type> operator()(T) const
    {
      return std::nullopt;
    }
  };
  Warlock(Abilities& abilities): Class(abilities, 8, 0)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 12;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 13;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Charisma;
  }
};

class TheFiendWarlock: public Warlock
{
public:
  TheFiendWarlock(Abilities& abilities): Warlock(abilities) {}
};
class TheGreatOldOneWarlock: public Warlock
{
public:
  TheGreatOldOneWarlock(Abilities& abilities): Warlock(abilities) {}
};