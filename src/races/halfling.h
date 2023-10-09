#pragma once
#include "ability.h"
#include "race.h"

class Halfling: public Race
{
public:
  enum class Type
  {
    LightfootHalfling = 0,
    StrongheartHalfling,
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
  Halfling(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Dexterity, 2);
  }
};

inline std::string TypeToString(const Halfling::Type& type)
{
  using Type = Halfling::Type;
  switch (type)
  {
    case Type::LightfootHalfling:
      return "LightfootHalfling";
    case Type::StrongheartHalfling:
      return "StrongheartHalfling";
    default:
      return "INVALID";
  }
}

class LightfootHalfling: public Halfling
{
public:
  LightfootHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 1);
  }
};

class StrongheartHalfling: public Halfling
{
public:
  StrongheartHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.AddToAbility(AbilityType::Constitution, 1);
  }
};
