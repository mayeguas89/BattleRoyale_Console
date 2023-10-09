#pragma once
#include "race.h"
#include "ability.h"

class Githyanki: public Race
{
public:
  Githyanki(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Intelligence, 1);
    abilities.AddToAbility(AbilityType::Strength, 2);
  }
};
