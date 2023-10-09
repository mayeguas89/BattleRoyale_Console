#pragma once
#include "class.h"
class Fighter: public Class
{
public:
  Fighter(Abilities& abilities): Class(abilities, 10, 6)
  {
    primary_hability_.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Strength);
    abilities.AddToAbility(AbilityType::Strength, 15);
    abilities.AddToAbility(AbilityType::Dexterity, 13);
    abilities.AddToAbility(AbilityType::Constitution, 14);
    abilities.AddToAbility(AbilityType::Intelligence, 10);
    abilities.AddToAbility(AbilityType::Wisdom, 12);
    abilities.AddToAbility(AbilityType::Charisma, 8);
  }
};