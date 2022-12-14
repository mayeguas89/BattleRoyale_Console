#pragma once
#include "race.h"

class Tiefling: public Race
{
public:
  enum class Type
  {
    AsmodeusTiefling,
    MephistophelesTiefling,
    ZarielTiefling
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
  Tiefling(Abilities& abilities): Race(abilities) {}
};

class AsmodeusTiefling: public Tiefling
{
public:
  AsmodeusTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Intelligence] += 2;
  }
};

class MephistophelesTiefling: public Tiefling
{
public:
  MephistophelesTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Intelligence] += 1;
  }
};

class ZarielTiefling: public Tiefling
{
public:
  ZarielTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.map[AbilityType::Charisma] += 2;
    abilities.map[AbilityType::Strength] += 1;
  }
};
