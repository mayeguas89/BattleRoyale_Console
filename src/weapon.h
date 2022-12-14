#pragma once
#include "dice.h"
class Weapon
{
public:
  enum class Type
  {
    MeleeWeapon,
    RangedWeapon,
    TwoHandedMeleeWeapon,
  };
  Weapon(int num_dices, int faces, Type type): num_dices_{num_dices}, faces_{faces}, type_{type} {}
  Weapon() = default;
  int GetDamage()
  {
    int damage = 0;
    for (int i = 0; i < num_dices_; i++)
    {
      damage += SingletonDice::Get().Roll(faces_);
    }
    return damage;
  }

  Type GetType()
  {
    return type_;
  }

protected:
  int num_dices_;
  int faces_;
  Type type_;
};
