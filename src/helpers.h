#pragma once
#include "ability.h"
#include "armor.h"
#include "weapon.h"

#include <optional>


namespace helpers
{
int GetAttackModifier(std::optional<Weapon>& weapon, const Abilities& abilities)
{
  if (!weapon)
    return 0;
  if (weapon->GetType() == Weapon::Type::RangedWeapon)
    return abilities.map[Ability::Type::Dexterity];
  return abilities.map[Ability::Type::Strength];
}
// Without Armor or a Shield, your character's AC equals 10 + their Dexterity modifier.
int GetArmorClass(int dexterity_modifier, std::optional<WearArmor> wear_armor, std::optional<Shield> shield)
{
  // If your character wears Armour, carries a shield, or both their AC will be used
  if (!wear_armor && !shield)
    return 10 + dexterity_modifier;

  int ac = 0;
  // Using a Shield will increase your AC by +2.
  if (shield)
    ac += shield->ac + 2;
  if (wear_armor)
  {
    switch (wear_armor->type)
    {
      case WearArmor::Type::LightArmor:
        //When wearing Light Armour you gain the full value of your Dexterity modifier added to your Armour Class.
        // OJO el dexterity modifier podria ser < 0 y perder puntos
        ac += wear_armor->ac + dexterity_modifier;
        break;
      case WearArmor::Type::MediumArmor:
        //When wearing Medium Armour, you gain up to +2 AC from your Dexterity modifier
        // OJO el dexterity modifier podria ser < 0 y perder puntos
        ac += wear_armor->ac;
        ac += dexterity_modifier > 2 ? 2 : dexterity_modifier;
        break;
      case WearArmor::Type::HeavyArmor:
        //When wearing Heavy Armour you gain no benefit from your Dexterity modifier at all.ac +=
        ac += wear_armor->ac;
        break;
      default:
        break;
    }
  }
}
}