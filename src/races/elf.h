#pragma once
#include "race.h"

class Elf: public Race
{
public:
  enum class Type
  {
    HighElf,
    WoodElf
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
  Elf(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 2;
  }
};

class HighElf: public Elf
{
public:
  HighElf(Abilities& abilities): Elf(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

class WoodElf: public Elf
{
public:
  WoodElf(Abilities& abilities): Elf(abilities)
  {
    abilities.map[AbilityType::Wisdom] += 1;
  }
};
