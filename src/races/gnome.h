#pragma once
#include "race.h"

class Gnome: public Race
{
public:
  enum class Type
  {
    DeepGnome=0,
    ForestGnome,
    RockGnome,
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
  Gnome(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

inline std::string TypeToString(const Gnome::Type& type)
{
  using Type = Gnome::Type;
  switch (type)
  {
    case Type::DeepGnome:
      return "DeepGnome";
    case Type::ForestGnome:
      return "ForestGnome";
    case Type::RockGnome:
      return "RockGnome";
    default:
      return "INVALID";
  }
}

class DeepGnome: public Gnome
{
public:
  DeepGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

class ForestGnome: public Gnome
{
public:
  ForestGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Dexterity] += 1;
  }
};

class RockGnome: public Gnome
{
public:
  RockGnome(Abilities& abilities): Gnome(abilities)
  {
    abilities.map[AbilityType::Constitution] += 1;
  }
};
