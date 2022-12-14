#pragma once
#include "class.h"
class Ranger: public Class
{
public:
  Ranger(Abilities& abilities): Class(abilities, 10, 0)
  {
    primary_hability_.push_back(AbilityType::Dexterity);
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Strength);
    abilities.map[AbilityType::Strength] += 12;
    abilities.map[AbilityType::Dexterity] += 15;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 14;
    abilities.map[AbilityType::Charisma] += 10;
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};