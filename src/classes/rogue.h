#pragma once
#include "class.h"

class Rogue: public Class
{
public:
  Rogue(Abilities& abilities): Class(abilities, 8, 5)
  {
    primary_hability_.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Intelligence);
    abilities.AddToAbility(AbilityType::Strength, 8);
    abilities.AddToAbility(AbilityType::Dexterity, 15);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 12);
    abilities.AddToAbility(AbilityType::Wisdom, 13);
    abilities.AddToAbility(AbilityType::Charisma, 10);
  }
};