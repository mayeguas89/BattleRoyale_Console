#pragma once

#include "ability.h"
#include "attack.h"
#include "status_effect.h"

#include <string>
#include <vector>

using AbilityType = Ability::Type;

class Spell: public NamedAttack
{
public:
  enum class DamageInflict
  {
    Acid,
    Necrotic,
    Lightning,
    Force,
    Piercing,
    Thunder,
    Bludgeoning,
    Cold,
    Radiant,
    Poison,
    Psychic,
    Fire,
    None
  };

  enum class EffectType
  {
    Damage = 0,
    Healing,
    None
  };

  Spell(const std::string& name,
        int num_dices,
        int faces,
        int level,
        AbilityType saving_throw,
        const std::vector<DamageInflict>& damage_inflict = {DamageInflict::None},
        EffectType effect_type = EffectType::Damage,
        int number_of_turns_taken = 1):
    NamedAttack(name, num_dices, faces),
    level_{level},
    saving_throw_{saving_throw},
    damage_inflict_{damage_inflict_},
    effect_type_{effect_type},
    number_of_turns_taken_{number_of_turns_taken}
  {}

  Spell(const Spell& other) = default;
  Spell() = default;

  AbilityType GetAbilityTypeSavingThrows() const
  {
    return saving_throw_;
  }

  int GetLevel() const
  {
    return level_;
  }

  const std::vector<DamageInflict>& GetDamageInflict() const
  {
    return damage_inflict_;
  }

protected:
  int number_of_turns_taken_;
  AbilityType saving_throw_;
  float saving_throws_half_reduction_;
  const std::vector<DamageInflict> damage_inflict_;
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
          const std::vector<DamageInflict>& damage_inflict = {DamageInflict::None},
          EffectType effect_type = EffectType::None,
          int number_of_turns_taken = 1):
    Spell(name, num_dices, faces, level, saving_throw, damage_inflict, effect_type, number_of_turns_taken)
  {}
};

inline std::string TypeToString(Spell::DamageInflict damage)
{
  switch (damage)
  {
    case Spell::DamageInflict::Acid:
      return "Acid";
    case Spell::DamageInflict::Necrotic:
      return "Necrotic";
    case Spell::DamageInflict::Lightning:
      return "Lightning";
    case Spell::DamageInflict::Force:
      return "Force";
    case Spell::DamageInflict::Piercing:
      return "Piercing";
    case Spell::DamageInflict::Thunder:
      return "Thunder";
    case Spell::DamageInflict::Bludgeoning:
      return "Bludgeoning";
    case Spell::DamageInflict::Cold:
      return "Cold";
    case Spell::DamageInflict::Radiant:
      return "Radiant";
    case Spell::DamageInflict::Poison:
      return "Poison";
    case Spell::DamageInflict::Psychic:
      return "Psychic";
    case Spell::DamageInflict::Fire:
      return "Fire";
  }
  return "UNDEFINED";
}

inline Spell::DamageInflict StringToDamageInflict(const std::string& damage)
{
  if (damage == "acid")
  {
    return Spell::DamageInflict::Acid;
  }
  if (damage == "necrotic")
  {
    return Spell::DamageInflict::Necrotic;
  }
  if (damage == "lightning")
  {
    return Spell::DamageInflict::Lightning;
  }
  if (damage == "force")
  {
    return Spell::DamageInflict::Force;
  }
  if (damage == "piercing")
  {
    return Spell::DamageInflict::Piercing;
  }
  if (damage == "thunder")
  {
    return Spell::DamageInflict::Thunder;
  }
  if (damage == "bludgeoning")
  {
    return Spell::DamageInflict::Bludgeoning;
  }
  if (damage == "cold")
  {
    return Spell::DamageInflict::Cold;
  }
  if (damage == "radiant")
  {
    return Spell::DamageInflict::Radiant;
  }
  if (damage == "poison")
  {
    return Spell::DamageInflict::Poison;
  }
  if (damage == "psychic")
  {
    return Spell::DamageInflict::Psychic;
  }
  if (damage == "fire")
  {
    return Spell::DamageInflict::Fire;
  }

  return Spell::DamageInflict::None;
}