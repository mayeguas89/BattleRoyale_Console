#pragma once
#include "class.h"

class Druid: public Class
{
public:
  Druid(Abilities& abilities): Class(abilities, 8, 5)
  {
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Intelligence);
    saving_throw.push_back(AbilityType::Wisdom);
    abilities.AddToAbility(AbilityType::Strength, 10);
    abilities.AddToAbility(AbilityType::Dexterity, 14);
    abilities.AddToAbility(AbilityType::Constitution, 13);
    abilities.AddToAbility(AbilityType::Intelligence, 8);
    abilities.AddToAbility(AbilityType::Wisdom, 15);
    abilities.AddToAbility(AbilityType::Charisma, 12);
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};
