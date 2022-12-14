#pragma once
#include "race.h"

class Human: public Race
{
public:
  Human(Abilities& abilities): Race(abilities)
  {
    for (auto& ability: abilities.map)
    {
      ability.second += 1;
    }
  }
};
