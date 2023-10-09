#pragma once
#include "ability.h"
#include "race.h"

class Tiefling: public Race
{
public:
  enum class Type
  {
    AsmodeusTiefling = 0,
    MephistophelesTiefling,
    ZarielTiefling,
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

  Tiefling(Abilities& abilities): Race(abilities) {}
};

inline std::string TypeToString(const Tiefling::Type& type)
{
  using Type = Tiefling::Type;
  switch (type)
  {
    case Type::AsmodeusTiefling:
      return "AsmodeusTiefling";
    case Type::MephistophelesTiefling:
      return "MephistophelesTiefling";
    case Type::ZarielTiefling:
      return "ZarielTiefling";
    default:
      return "INVALID";
  }
}

class AsmodeusTiefling: public Tiefling
{
public:
  AsmodeusTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 2);
    abilities.AddToAbility(AbilityType::Intelligence, 2);
  }
};

class MephistophelesTiefling: public Tiefling
{
public:
  MephistophelesTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 2);
    abilities.AddToAbility(AbilityType::Intelligence, 1);
  }
};

class ZarielTiefling: public Tiefling
{
public:
  ZarielTiefling(Abilities& abilities): Tiefling(abilities)
  {
    abilities.AddToAbility(AbilityType::Charisma, 2);
    abilities.AddToAbility(AbilityType::Strength, 1);
  }
};
