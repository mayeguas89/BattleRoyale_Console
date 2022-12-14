#pragma once
#include "class.h"
class Fighter: public Class
{
public:
  Fighter(Abilities& abilities): Class(abilities, 10, 0)
  {
    primary_hability_.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Constitution);
    saving_throw.push_back(AbilityType::Strength);
    abilities.map[AbilityType::Strength] += 15;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 10;
    abilities.map[AbilityType::Wisdom] += 12;
    abilities.map[AbilityType::Charisma] += 8;
  }
};