#pragma once

#include "class.h"

class Wizard: public Class
{
public:
  Wizard(Abilities& abilities): Class(abilities, 6, 4)
  {
    primary_hability_.push_back(AbilityType::Intelligence);
    saving_throw.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Intelligence);
    abilities.AddToAbility(AbilityType::Strength, 8);
    abilities.AddToAbility(AbilityType::Dexterity, 13);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 15);
    abilities.AddToAbility(AbilityType::Wisdom, 10);
    abilities.AddToAbility(AbilityType::Charisma, 12);
  }

  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Intelligence;
  }
};