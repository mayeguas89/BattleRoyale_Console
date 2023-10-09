#pragma once
#include "class.h"
class Sorcerer: public Class
{
public:
  enum class Type
  {
    WildMagicSorcerer = 0,
    DraconicBloodlineSorcerer,
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
  Sorcerer(Abilities& abilities): Class(abilities, 6, 4)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.AddToAbility(AbilityType::Strength, 8);
    abilities.AddToAbility(AbilityType::Dexterity, 13);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 12);
    abilities.AddToAbility(AbilityType::Wisdom, 10);
    abilities.AddToAbility(AbilityType::Charisma, 15);
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Charisma;
  }
};
class WildMagicSorcerer: public Sorcerer
{
public:
  WildMagicSorcerer(Abilities& abilities): Sorcerer(abilities) {}
};
class DraconicBloodlineSorcerer: public Sorcerer
{
public:
  DraconicBloodlineSorcerer(Abilities& abilities): Sorcerer(abilities) {}
};

inline std::string TypeToString(const Sorcerer::Type& type)
{
  using Type = Sorcerer::Type;
  switch (type)
  {
    case Type::WildMagicSorcerer:
      return "WildMagicSorcerer";
    case Type::DraconicBloodlineSorcerer:
      return "DraconicBloodlineSorcerer";
    default:
      return "INVALID";
  }
}