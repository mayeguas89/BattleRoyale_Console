#pragma once

#include "class.h"

class Warlock: public Class
{
public:
  enum class Type
  {
    TheFiendWarlock=0,
    TheGreatOldOneWarlock,
    None
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
  Warlock(Abilities& abilities): Class(abilities, 8, 5)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.AddToAbility(AbilityType::Strength, 8);
    abilities.AddToAbility(AbilityType::Dexterity, 12);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 13);
    abilities.AddToAbility(AbilityType::Wisdom, 10);
    abilities.AddToAbility(AbilityType::Charisma, 15);
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


inline std::string TypeToString(const Warlock::Type& type)
{
  using Type = Warlock::Type;
  switch (type)
  {
    case Type::TheFiendWarlock:
      return "TheFiendWarlock";
    case Type::TheGreatOldOneWarlock:
      return "TheGreatOldOneWarlock";
    default:
      return "INVALID";
  }
}