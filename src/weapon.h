#pragma once
#include "ability.h"
#include "attack.h"

#include <fmt/core.h>

class Weapon: public NamedAttack
{
public:
  enum class DamageType
  {
    Bludgeoning,
    Slashing,
    Piercing,
    None
  };

  Weapon(const std::string& name, int num_dices, int faces, DamageType damageType):
    NamedAttack(name, num_dices, faces),
    damageType_{damageType}
  {}

  Weapon() = default;

  virtual ~Weapon() = default;

  // Copy constructor
  Weapon(const Weapon& weapon): NamedAttack(weapon)
  {
    damageType_ = weapon.damageType_;
  }

  Weapon& operator=(const Weapon& other)
  {
    NamedAttack::operator=(other);
    return *this;
  }

  virtual Ability::Type GetAttackAbilityModifier()
  {
    return Ability::Type::None;
  }

  DamageType GetDamageType() const
  {
    return damageType_;
  }
  friend std::ostream& operator<<(std::ostream& os, const Weapon& w);

protected:
  DamageType damageType_;
};

class MeleeWeapon: public Weapon
{
public:
  MeleeWeapon(const std::string& name, int num_dices, int faces, DamageType damageType):
    Weapon(name, num_dices, faces, damageType)
  {}
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
  RangedWeapon(const std::string& name, int num_dices, int faces, DamageType damageType):
    Weapon(name, num_dices, faces, damageType)
  {}

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

inline Weapon::DamageType StringToDamageType(const std::string& damage_type)
{
  if (damage_type == "Bludgeoning")
    return Weapon::DamageType::Bludgeoning;
  if (damage_type == "Slashing")
    return Weapon::DamageType::Slashing;
  if (damage_type == "Piercing")
    return Weapon::DamageType::Piercing;
  return Weapon::DamageType::None;
}

inline std::string DamageTypeToString(Weapon::DamageType damage_type)
{
  switch (damage_type)
  {
    case Weapon::DamageType::Bludgeoning:
      return "Bludgeoning";
    case Weapon::DamageType::Slashing:
      return "Slashing";
    case Weapon::DamageType::Piercing:
      return "Piercing";
  }
  return "UNDEFINED";
}

template<>
struct fmt::formatter<Weapon>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const Weapon& w, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{Name: {}, Damage: {}d{}, DamageType: {}}}",
                            w.GetName(),
                            w.GetNumDices(),
                            w.GetFaces(),
                            DamageTypeToString(w.GetDamageType()));

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};