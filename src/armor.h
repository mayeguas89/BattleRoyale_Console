#pragma once

// https://baldursgate3.wiki.fextralife.com/Armour+Class
struct Shield;

struct Armor
{
  Armor(int p_ac): ac{p_ac} {}
  int ac;
};

struct Shield: public Armor
{
  Shield(int p_ac): Armor(p_ac) {}
};

struct WearArmor: public Armor
{
  enum class Type
  {
    LightArmor,
    MediumArmor,
    HeavyArmor
  };
  WearArmor(int p_ac, Type p_type): Armor(p_ac), type{p_type} {}
  Type type;
};
