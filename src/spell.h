#pragma once

#include "ability.h"
#include "attack.h"
#include "status_effect.h"

#include <string>
using AbilityType = Ability::Type;
// A Speel can only be casted once
class Spell: public Attack
{
public:
  Spell(const std::string& name,
        int num_dices,
        int faces,
        AbilityType saving_throw,
        StatusEffect status_effect = StatusEffect::None,
        int number_of_turns_taken = 1):
    Attack(num_dices, faces),
    name_{name},
    saving_throw_{saving_throw},
    number_of_turns_taken_{number_of_turns_taken},
    status_effect_{status_effect}
  {}

  AbilityType GetAbilityTypeSavingThrows() const
  {
    return saving_throw_;
  }

protected:
  std::string name_;
  int number_of_turns_taken_;
  AbilityType saving_throw_;
  float saving_throws_half_reduction_;
  StatusEffect status_effect_;
};

/**
 * @brief A cantrip is a spell that can be cast at will, without
 * using a spell slot and without being prepared in
 * advance.
 * 
 */
class Cantrip: public Spell
{
public:
  Cantrip(const std::string& name,
          int num_dices,
          int faces,
          AbilityType saving_throw,
          StatusEffect status_effect = StatusEffect::None,
          int number_of_turns_taken = 1):
    Spell(name, num_dices, faces, saving_throw, status_effect, number_of_turns_taken)
  {}
};