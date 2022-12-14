#pragma once
#include "race.h"

class Drow: public Race
{
public:
  enum class Type
  {
    LolthSwornDrow,
    SeldarineDrow
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
    abilities.map[AbilityType::Charisma] += 1;
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

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
