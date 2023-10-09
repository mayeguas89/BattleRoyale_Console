#pragma once
#include "ability.h"
#include "race.h"

class Human: public Race
{
public:
  Human(Abilities& abilities): Race(abilities)
  {
    abilities.AddToAbility(AbilityType::Strength, 1);
    abilities.AddToAbility(AbilityType::Dexterity, 1);
    abilities.AddToAbility(AbilityType::Constitution, 1);
    abilities.AddToAbility(AbilityType::Intelligence, 1);
    abilities.AddToAbility(AbilityType::Wisdom, 1);
    abilities.AddToAbility(AbilityType::Charisma, 1);
  }
};
