#pragma once
#include "class.h"
class Ranger: public Class
{
public:
  Ranger(Abilities& abilities): Class(abilities, 10, 6)
  {
    primary_hability_.push_back(AbilityType::Dexterity);
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Strength);
    abilities.AddToAbility(AbilityType::Strength, 12);
    abilities.AddToAbility(AbilityType::Dexterity, 15);
    abilities.AddToAbility(AbilityType::Constitution, 13);
    abilities.AddToAbility(AbilityType::Intelligence, 8);
    abilities.AddToAbility(AbilityType::Wisdom, 14);
    abilities.AddToAbility(AbilityType::Charisma, 10);
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};