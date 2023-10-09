#pragma once
#include "ability.h"
#include "race.h"

class HalfElf: public Race
{
public:
  enum class Type
  {
    HighHalfElf = 0,
    WoodHalfElf,
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
  HalfElf(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 2);
    abilities.AddToAbility(AbilityType::Strength, 2);
  }
};

inline std::string TypeToString(const HalfElf::Type& type)
{
  using Type = HalfElf::Type;
  switch (type)
  {
    case Type::HighHalfElf:
      return "HighHalfElf";
    case Type::WoodHalfElf:
      return "WoodHalfElf";
    default:
      return "INVALID";
  }
}

class HighHalfElf: public HalfElf
{
public:
  HighHalfElf(Abilities& abilities): HalfElf(abilities) {}
};

class WoodHalfElf: public HalfElf
{
public:
  WoodHalfElf(Abilities& abilities): HalfElf(abilities) {}
};
