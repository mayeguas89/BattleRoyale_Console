#pragma once

#include "class.h"

#include <optional>


class Cleric: public Class
{
public:
  enum class Type
  {
    LifeDomainCleric=0,
    LightDomainCleric,
    TrickeryDomainCleric,
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
  Cleric(Abilities& abilities): Class(abilities, 8, 0)
  {
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Charisma);
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};

class LifeDomainCleric: public Cleric
{
public:
  LifeDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 14;
    abilities.map[AbilityType::Dexterity] += 10;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
};

class LightDomainCleric: public Cleric
{
public:
  LightDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 10;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
};

class TrickeryDomainCleric: public Cleric
{
public:
  TrickeryDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.map[AbilityType::Strength] += 12;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 10;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 8;
  }
};

inline std::string TypeToString(const Cleric::Type& type)
{
  using Type = Cleric::Type;
  switch (type)
  {
    case Type::LifeDomainCleric:
      return "LifeDomainCleric";
    case Type::LightDomainCleric:
      return "LightDomainCleric";
    case Type::TrickeryDomainCleric:
      return "TrickeryDomainCleric";
    default:
      return "INVALID";
  }
}