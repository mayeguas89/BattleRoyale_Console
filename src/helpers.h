#pragma once
#include "ability.h"
#include "armor.h"
#include "weapon.h"

#include <memory>
#include <optional>


namespace helpers
{
int GetArmorClass(int dexterity_modifier,
                  const std::shared_ptr<WearArmor>& wear_armor,
                  const std::shared_ptr<Shield>& shield)
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