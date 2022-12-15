#pragma once
#include "ability.h"
#include "attack.h"

class Weapon: public NamedAttack
{
public:
  Weapon(const std::string& name, int num_dices, int faces): NamedAttack(name, num_dices, faces) {}

  Weapon() = default;

  virtual ~Weapon() = default;

  // Copy constructor
  Weapon(const Weapon& weapon): NamedAttack(weapon) {}

  Weapon& operator=(const Weapon& other)
  {
    NamedAttack::operator=(other);
    return *this;
  }

  virtual Ability::Type GetAttackAbilityModifier()
  {
    return Ability::Type::None;
  }
};

class MeleeWeapon: public Weapon
{
public:
  MeleeWeapon(const std::string& name, int num_dices, int faces): Weapon(name, num_dices, faces) {}
  ~MeleeWeapon()
  {
    Weapon::~Weapon();
  }
  MeleeWeapon(const Weapon& weapon): Weapon(weapon) {}

  Ability::Type GetAttackAbilityModifier() override
  {
    return Ability::Type::Strength;
  }
};

class RangedWeapon: public Weapon
{
public:
  RangedWeapon(const std::string& name, int num_dices, int faces): Weapon(name, num_dices, faces) {}

  RangedWeapon(const Weapon& weapon): Weapon(weapon) {}
  ~RangedWeapon()
  {
    Weapon::~Weapon();
  }
  Ability::Type GetAttackAbilityModifier() override
  {
    return Ability::Type::Dexterity;
  }
};