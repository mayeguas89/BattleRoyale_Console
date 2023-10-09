#pragma once

#include "item.h"

#include <fmt/format.h>

class Armor: public Item
{
public:
  Armor(const std::string& name, int ac): Item(name), ac_{ac} {}

  Armor() = default;

  Armor(const Armor& other): Item(other), ac_{other.ac_} {}

  Armor& operator=(const Armor& other)
  {
    Item::operator=(other);
    return *this;
  };

  virtual ~Armor() = default;

  int GetArmorClass() const
  {
    return ac_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Armor& a);

protected:
  int ac_;
};

inline std::ostream& operator<<(std::ostream& os, const Armor& a)
{
  return os << fmt::format("{{Name: {}, AC: {}}}", a.GetName(), a.GetArmorClass()) << std::endl;
}

class Shield: public Armor
{
public:
  Shield(const std::string& name, int ac): Armor(name, ac) {}
};

class WearArmor: public Armor
{
public:
  WearArmor(const std::string& name, int ac): Armor(name, ac) {}

  WearArmor() = default;

  WearArmor(const WearArmor& armor): Armor(armor) {}

  WearArmor& operator=(const WearArmor& other)
  {
    Armor::operator=(other);
    return *this;
  };

  virtual ~WearArmor() = default;

  virtual int GetWearArmorClass(int dexterity_modifier) const
  {
    return 0;
  };
};

class LightArmor: public WearArmor
{
public:
  LightArmor(const std::string& name, int ac): WearArmor(name, ac) {}

  LightArmor(const LightArmor& armor): WearArmor(armor) {}

  /**
   * @brief Get the Wear Armor Class object
   * 
   * @param dexterity_modifier 
   * @return int 
   */
  int GetWearArmorClass(int dexterity_modifier) const override
  {
    return ac_ + dexterity_modifier;
  }
};

class MediumArmor: public WearArmor
{
public:
  MediumArmor(const std::string& name, int ac): WearArmor(name, ac) {}

  MediumArmor(const MediumArmor& armor): WearArmor(armor) {}

  /**
   * @brief Get the Wear Armor Class object
   * 
   * @param dexterity_modifier 
   * @return int 
   */
  int GetWearArmorClass(int dexterity_modifier) const override
  {
    int ac_modifier = dexterity_modifier > 2 ? 2 : dexterity_modifier;
    return ac_ + ac_modifier;
  }
};

class HeavyArmor: public WearArmor
{
public:
  HeavyArmor(const std::string& name, int ac): WearArmor(name, ac) {}

  HeavyArmor(const HeavyArmor& armor): WearArmor(armor) {}
  
  /**
   * @brief Get the Wear Armor Class object
   * 
   * @param dexterity_modifier 
   * @return int 
   */
  int GetWearArmorClass(int dexterity_modifier) const override
  {
    return ac_;
  }
};

template<>
struct fmt::formatter<WearArmor>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const WearArmor& a, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{Name: {}, AC: {}}}", a.GetName(), a.GetArmorClass());

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};

template<>
struct fmt::formatter<Shield>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const Shield& a, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{Name: {}, AC: {}}}", a.GetName(), a.GetArmorClass());

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};