#pragma once

#include "ability.h"
#include "attack.h"
#include "status_effect.h"

#include <string>
using AbilityType = Ability::Type;
// A Speel can only be casted once
class Spell: public NamedAttack
{
public:
  enum class EffectType
  {
    Damage=0,
    Healing,
    None
  };

  Spell(const std::string& name,
        int num_dices,
        int faces,
        int level,
        AbilityType saving_throw,
        EffectType effect_type = EffectType::Damage,
        StatusEffect status_effect = StatusEffect::None,
        int number_of_turns_taken = 1):
    NamedAttack(name, num_dices, faces),
    level_{level},
    saving_throw_{saving_throw},
    effect_type_{effect_type},
    number_of_turns_taken_{number_of_turns_taken},
    status_effect_{status_effect}
  {}

  Spell(const Spell& other) = default;
  Spell() = default;

  AbilityType GetAbilityTypeSavingThrows() const
  {
    return saving_throw_;
  }

protected:
  int number_of_turns_taken_;
  AbilityType saving_throw_;
  float saving_throws_half_reduction_;
  StatusEffect status_effect_;
  EffectType effect_type_;
  int level_;
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
          int level,
          AbilityType saving_throw,
          EffectType effect_type = EffectType::None,
          StatusEffect status_effect = StatusEffect::None,
          int number_of_turns_taken = 1):
    Spell(name, num_dices, faces, level, saving_throw, effect_type, status_effect, number_of_turns_taken)
  {}
};