#pragma once
#include "race.h"

class Halfling: public Race
{
public:
  enum class Type
  {
    LightfootHalfling,
    StrongheartHalfling
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
    abilities.map[AbilityType::Dexterity] += 2;
  }
};

class LightfootHalfling: public Halfling
{
public:
  LightfootHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 1;
  }
};

class StrongheartHalfling: public Halfling
{
public:
  StrongheartHalfling(Abilities& abilities): Halfling(abilities)
  {
    abilities.map[AbilityType::Constitution] += 1;
  }
};
