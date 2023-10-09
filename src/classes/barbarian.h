#pragma once

#include "class.h"

class Barbarian: public Class
{
public:
  Barbarian(Abilities& abilities): Class(abilities, 12, 5)
  {
    primary_hability_.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Constitution);
    abilities.AddToAbility(AbilityType::Strength, 15);
    abilities.AddToAbility(AbilityType::Dexterity, 13);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 8);
    abilities.AddToAbility(AbilityType::Wisdom, 12);
    abilities.AddToAbility(AbilityType::Charisma, 10);
  }
};