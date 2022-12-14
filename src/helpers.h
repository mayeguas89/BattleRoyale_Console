#pragma once
#include "ability.h"
#include "armor.h"
#include "weapon.h"

#include <optional>

namespace helpers
{
int GetArmorClass(int dexterity_modifier, std::optional<WearArmor> wear_armor, std::optional<Shield> shield)
{
  if (!wear_armor && !shield)
    return 10 + dexterity_modifier;

  int ac = 0;

  if (shield)
    ac += shield->GetArmorClass() + 2;

  if (wear_armor)
    ac += wear_armor->GetWearArmorClass(dexterity_modifier);

  return ac;
}

}