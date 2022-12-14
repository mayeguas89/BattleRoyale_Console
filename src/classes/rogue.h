#pragma once
#include "class.h"

class Rogue: public Class
{
public:
  Rogue(Abilities& abilities): Class(abilities, 8, 0)
  {
    primary_hability_.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Intelligence);
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 15;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 13;
    abilities.map[AbilityType::Charisma] += 10;
  }
};