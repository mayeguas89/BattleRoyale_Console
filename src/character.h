#pragma once
#include "ability.h"
#include "class.h"
#include "race.h"

#include <unordered_map>

class Character
{
public:
  Character(std::unordered_map<Ability::Type, Ability> abilities_map, std::unique_ptr<Race> race):
    abilities_map_{abilities_map},
    race_{std::move(race)}
  {}

protected:
  std::unordered_map<Ability::Type, Ability> abilities_map_;

  //   Class& class_;
  std::unique_ptr<Race> race_;

  int number_of_spell_slots_ = 0;
  int hit_die_ = 0;
};