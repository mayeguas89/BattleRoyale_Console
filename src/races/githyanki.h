#pragma once
#include "race.h"

class Githyanki: public Race
{
public:
  Githyanki(Abilities& abilities): Race(abilities)
  {
    abilities.map[AbilityType::Intelligence] += 1;
    abilities.map[AbilityType::Strength] += 2;
  }
};
