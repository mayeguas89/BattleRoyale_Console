#pragma once
#include "ability.h"
#include "armor.h"
#include "class.h"
#include "helpers.h"
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

  int GetArmorClass()
  {
    return helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
  }

  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipWearAmor(WearArmor wear_armor)
  {
    int previous_ac =
      helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
    int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor, shield_);
    if (new_ac > previous_ac)
      wear_armor_ = wear_armor;
  }
  // Logica: Si el AC es menor que el que da la armadura actual no se equipa
  void EquipShield(Shield shield)
  {
    int previous_ac =
      helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
    int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield);
    if (new_ac > previous_ac)
      shield_ = shield;
  }

protected:
  Abilities abilities_;

  std::optional<WearArmor> wear_armor_;
  std::optional<Shield> shield_;

  std::unique_ptr<Race> race_;
  std::unique_ptr<Class> class_;

  int number_of_spell_slots_ = 0;
  int hit_die_ = 0;
};