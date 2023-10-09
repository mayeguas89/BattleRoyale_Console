#pragma once
#include "ability.h"
#include "race.h"

class Dwarf: public Race
{
public:
  enum class Type
  {
    GoldDwarf = 0,
    ShieldDwarf,
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

  Dwarf(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Constitution, 2);
  }
};

inline std::string TypeToString(const Dwarf::Type& type)
{
  using Type = Dwarf::Type;
  switch (type)
  {
    case Type::GoldDwarf:
      return "GoldDwarf";
    case Type::ShieldDwarf:
      return "ShieldDwarf";
    default:
      return "INVALID";
  }
}

class GoldDwarf: public Dwarf
{
public:
  GoldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.AddToAbility(AbilityType::Wisdom, 1);
  }
};

class ShieldDwarf: public Dwarf
{
public:
  ShieldDwarf(Abilities& abilities): Dwarf(abilities)
  {
    abilities.AddToAbility(AbilityType::Strength, 2);
  }
};
