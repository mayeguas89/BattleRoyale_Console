#pragma once

#include "class.h"

class Bard: public Class
{
public:
  Bard(Abilities& abilities): Class(abilities, 8, 4)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.AddToAbility(AbilityType::Strength, 8);
    abilities.AddToAbility(AbilityType::Dexterity, 14);
    abilities.AddToAbility(AbilityType::Constitution, 13);
    abilities.AddToAbility(AbilityType::Intelligence, 12);
    abilities.AddToAbility(AbilityType::Wisdom, 10);
    abilities.AddToAbility(AbilityType::Charisma, 15);
  }

  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Charisma;
  }
};