#pragma once
#include "race.h"

#include "ability.h"
class Drow: public Race
{
public:
  enum class Type
  {
    LolthSwornDrow=0,
    SeldarineDrow,
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
  Drow(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 1);
    abilities.AddToAbility(AbilityType::Dexterity, 1);
  }
};

inline std::string TypeToString(const Drow::Type& type)
{
  using Type = Drow::Type;
  switch (type)
  {
    case Type::LolthSwornDrow:
      return "LolthSwornDrow";
    case Type::SeldarineDrow:
      return "SeldarineDrow";
    default:
      return "INVALID";
  }
}

class LolthSwornDrow: public Drow
{
public:
  LolthSwornDrow(Abilities& abilities): Drow(abilities) {}
};

class SeldarineDrow: public Drow
{
public:
  SeldarineDrow(Abilities& abilities): Drow(abilities) {}
};
