#pragma once
#include "ability.h"

using AbilityType = Ability::Type;

class Race
{
public:
  enum class Type
  {
    Dwarf,
    Elf,
    Halfling,
    Human,
    Githyanki,
    HalfElf,
    Tiefling,
    Drow,
    Gnome
  };

  Race(Abilities& abilities) {}
  virtual ~Race() = default;

protected:
};
