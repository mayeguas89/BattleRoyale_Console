#pragma once
#include "race.h"

class Dwarf: public Race
{
public:
  enum class Type
  {
    GoldDwarf,
    ShieldDwarf
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

  Dwarf(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Constitution] += 2;
  }
};

class GoldDwarf: public Dwarf
{
public:
  GoldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.map[AbilityType::Wisdom] += 1;
  }
};

class ShieldDwarf: public Dwarf
{
public:
  ShieldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.map[AbilityType::Strength] += 2;
  }
};
