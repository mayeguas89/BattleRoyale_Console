#pragma once
#include "attack.h"

class Weapon: public Attack
{
public:
  Weapon(const std::string& name, int num_dices, int faces): Attack(num_dices, faces), name_{name} {}
  Weapon() = default;
  virtual Ability::Type GetAttackAbilityModifier()
  {
    return Ability::Type::None;
  }

protected:
  std::string name_;
};

class MeleeWeapon: public Weapon
{
public:
  MeleeWeapon(const std::string& name, int num_dices, int faces): Weapon(name, num_dices, faces) {}
  Ability::Type GetAttackAbilityModifier() override
  {
    return Ability::Type::Strength;
  }
};

class RangedWeapon: public Weapon
{
public:
  RangedWeapon(const std::string& name, int num_dices, int faces): Weapon(name, num_dices, faces) {}
  Ability::Type GetAttackAbilityModifier() override
  {
    return Ability::Type::Dexterity;
  }
};