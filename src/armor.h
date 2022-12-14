#pragma once

// https://baldursgate3.wiki.fextralife.com/Armour+Class
class Armor
{
public:
  Armor(int ac): ac_{ac} {}
  virtual ~Armor() = default;
  int GetArmorClass()
  {
    return ac_;
  }

protected:
  int ac_;
};

class Shield: public Armor
{
public:
  Shield(int ac): Armor(ac) {}
};

class WearArmor: public Armor
{
public:
  WearArmor(int ac): Armor(ac) {}
  virtual ~WearArmor() = default;
  virtual int GetWearArmorClass(int dexterity_modifier)
  {
    return 0;
  };
};

class LightArmor: public WearArmor
{
public:
  LightArmor(int ac): WearArmor(ac) {}
  int GetWearArmorClass(int dexterity_modifier) override
  {
    return ac_ + dexterity_modifier;
  }
};

class MediumArmor: public WearArmor
{
public:
  MediumArmor(int ac): WearArmor(ac) {}
  int GetWearArmorClass(int dexterity_modifier) override
  {
    return ac_ + dexterity_modifier > 2 ? 2 : dexterity_modifier;
  }
};

class HeavyArmor: public WearArmor
{
public:
  HeavyArmor(int ac): WearArmor(ac) {}
  int GetWearArmorClass(int dexterity_modifier) override
  {
    return ac_;
  }
};