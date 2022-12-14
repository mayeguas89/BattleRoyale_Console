#pragma once

#include "class.h"

class Barbarian: public Class
{
public:
  Barbarian(Abilities& abilities): Class(abilities, 12, 0)
  {
    primary_hability_.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Strength);
    saving_throw.push_back(AbilityType::Constitution);
    abilities.map[AbilityType::Strength] += 15;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 12;
    abilities.map[AbilityType::Charisma] += 10;
  }
};