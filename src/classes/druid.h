#pragma once
#include "class.h"

class Druid: public Class
{
public:
  Druid(Abilities& abilities): Class(abilities, 8, 0)
  {
    primary_hability_.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Intelligence);
    saving_throw.push_back(AbilityType::Wisdom);
    abilities.map[AbilityType::Strength] += 10;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 8;
    abilities.map[AbilityType::Wisdom] += 15;
    abilities.map[AbilityType::Charisma] += 12;
  }
  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Wisdom;
  }
};
