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
  Cleric(Abilities& abilities): Class(abilities, 8, 5)
  {
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Charisma);
  }

  /**
   * @brief Get the Spell Casting Ability object
   * 
   * @return AbilityType 
   */
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};

/**
 * @brief Definicion de la clase LifeDomainCleric
 * 
 */
class LifeDomainCleric: public Cleric
{
public:
  LifeDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.AddToAbility(AbilityType::Strength, 14);
    abilities.AddToAbility(AbilityType::Dexterity, 10);
    abilities.AddToAbility(AbilityType::Constitution, 13);
    abilities.AddToAbility(AbilityType::Intelligence, 8);
    abilities.AddToAbility(AbilityType::Wisdom, 15);
    abilities.AddToAbility(AbilityType::Charisma, 12);
  }
};
/**
 * @brief Definicion de la clase LightDomainCleric
 * 
 */
class LightDomainCleric: public Cleric
{
public:
  LightDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.AddToAbility(AbilityType::Strength, 10);
    abilities.AddToAbility(AbilityType::Dexterity, 14);
    abilities.AddToAbility(AbilityType::Constitution, 13);
    abilities.AddToAbility(AbilityType::Intelligence, 8);
    abilities.AddToAbility(AbilityType::Wisdom, 15);
    abilities.AddToAbility(AbilityType::Charisma, 12);
  }
};
/**
 * @brief Definicion de la clase TrickeryDomainCleric
 * 
 */
class TrickeryDomainCleric: public Cleric
{
public:
  TrickeryDomainCleric(Abilities& abilities): Cleric(abilities)
  {
    abilities.AddToAbility(AbilityType::Strength, 12);
    abilities.AddToAbility(AbilityType::Dexterity, 13);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 10);
    abilities.AddToAbility(AbilityType::Wisdom, 15);
    abilities.AddToAbility(AbilityType::Charisma, 8);
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