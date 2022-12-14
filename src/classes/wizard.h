#pragma once

#include "class.h"

class Wizard: public Class
{
public:
  Wizard(Abilities& abilities): Class(abilities, 6, 0)
  {
    primary_hability_.push_back(AbilityType::Intelligence);
    saving_throw.push_back(AbilityType::Wisdom);
    saving_throw.push_back(AbilityType::Intelligence);
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 13;
    abilities.map[AbilityType::Constitution] += 14;
    abilities.map[AbilityType::Intelligence] += 15;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 12;
  }

  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Intelligence;
  }
};