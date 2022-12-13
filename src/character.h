#pragma once
#include "ability.h"
#include "class.h"
#include "race.h"

#include <unordered_map>

class Character
{
public:
  Character(Abilities abilities, std::unique_ptr<Race> race, std::unique_ptr<Class> p_class):
    abilities_{abilities},
    race_{std::move(race)},
    class_{std::move(p_class)}
  {}

  std::optional<Ability> GetAbility(Ability::Type type)
  {
    if (auto it = abilities_.map.find(type); it != abilities_.map.end())
    {
      return it->second;
    }
    return std::nullopt;
  }

protected:
  Abilities abilities_;

  std::unique_ptr<Race> race_;
  std::unique_ptr<Class> class_;

  int number_of_spell_slots_ = 0;
  int hit_die_ = 0;
};