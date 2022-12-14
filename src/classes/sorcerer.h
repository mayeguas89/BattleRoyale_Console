#pragma once
#include "class.h"
class Sorcerer: public Class
{
public:
  enum class Type
  {
    WildMagicSorcerer,
    DraconicBloodlineSorcerer
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
  Sorcerer(Abilities& abilities): Class(abilities, 6, 0)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
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