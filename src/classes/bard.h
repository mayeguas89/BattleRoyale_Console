#pragma once

#include "class.h"

class Bard: public Class
{
public:
  Bard(Abilities& abilities): Class(abilities, 8, 0)
  {
    primary_hability_.push_back(AbilityType::Charisma);
    saving_throw.push_back(AbilityType::Dexterity);
    saving_throw.push_back(AbilityType::Charisma);
    abilities.map[AbilityType::Strength] += 8;
    abilities.map[AbilityType::Dexterity] += 14;
    abilities.map[AbilityType::Constitution] += 13;
    abilities.map[AbilityType::Intelligence] += 12;
    abilities.map[AbilityType::Wisdom] += 10;
    abilities.map[AbilityType::Charisma] += 15;
  }

  AbilityType GetSpellCastingAbility() override
  {
    return AbilityType::Charisma;
  }
};