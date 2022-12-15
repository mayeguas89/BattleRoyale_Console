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

inline std::string TypeToString(const Race::Type& type)
{
  using Type = Race::Type;
  switch (type)
  {
    case Type::Dwarf:
      return "Dwarf";
    case Type::Elf:
      return "Elf";
    case Type::Halfling:
      return "Halfling";
    case Type::Human:
      return "Human";
    case Type::Githyanki:
      return "Githyanki";
    case Type::HalfElf:
      return "HalfElf";
    case Type::Tiefling:
      return "Tiefling";
    case Type::Drow:
      return "Drow";
    case Type::Gnome:
      return "Gnome";
    default:
      return "INVALID";
  }
}