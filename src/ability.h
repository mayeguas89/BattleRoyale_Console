#pragma once

#include <fmt/format.h>
#include <tabulate/table.hpp>

#include <unordered_map>

class Ability
{
public:
  static const int kMaxAbility = 24;
  enum class Type
  {
    Strength = 0,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma,
    None
  };

  Ability(): score_{0}, modifier_{0} {}

  Ability(int p_value): score_{p_value}
  {
    CalculateModifier();
  }

  friend void operator+=(Ability& ability, int value);

  int GetModifier() const
  {
    return modifier_;
  }

  int GetScore() const
  {
    return score_;
  }

  void SetScore(int value)
  {
    value = std::min(value, kMaxAbility);
    score_ = value;
    CalculateModifier();
  }

private:
  int score_;
  int modifier_;

  void CalculateModifier()
  {
    float tmp = (score_ - 10) / 2.f;
    modifier_ = static_cast<int>(std::floor(tmp));
  }
};

inline void operator+=(Ability& ability, int value)
{
  ability.score_ += value;
  ability.CalculateModifier();
}

class Abilities
{
public:
  Abilities();

  std::unordered_map<Ability::Type, Ability> GetMap()
  {
    return map_;
  }

  tabulate::Table GetAbilitiesTable()
  {
    return abilities_table_;
  }

  void SetAbility(Ability::Type type, Ability ability)
  {
    map_[type] = ability;

    SetAbilitiesTable();
  }

  void AddToAbility(Ability::Type type, int value)
  {
    map_[type] += value;

    SetAbilitiesTable();
  }

  Ability GetAbility(Ability::Type type) const
  {
    return map_.find(type)->second;
  }

  void SetAbilitiesTable();

  friend std::ostream& operator<<(std::ostream& os, const Abilities& abilities);

private:
  std::unordered_map<Ability::Type, Ability> map_;

  tabulate::Table abilities_table_;
};

inline std::string AbilityTypeToString(Ability::Type type)
{
  switch (type)
  {
    case Ability::Type::Strength:
      return "Strength";
    case Ability::Type::Dexterity:
      return "Dexterity";
    case Ability::Type::Constitution:
      return "Constitution";
    case Ability::Type::Intelligence:
      return "Intelligence";
    case Ability::Type::Wisdom:
      return "Wisdom";
    case Ability::Type::Charisma:
      return "Charisma";
  }
  return "None";
}

inline Ability::Type StringToAbilityType(const std::string& type)
{
  if (type == "Strength")
    return Ability::Type::Strength;
  if (type == "Dexterity")
    return Ability::Type::Dexterity;
  if (type == "Constitution")
    return Ability::Type::Constitution;
  if (type == "Intelligence")
    return Ability::Type::Intelligence;
  if (type == "Wisdom")
    return Ability::Type::Wisdom;
  if (type == "Charisma")
    return Ability::Type::Charisma;
  return Ability::Type::None;
}

inline std::ostream& operator<<(std::ostream& os, const Abilities& abilities)
{
  return os << abilities.abilities_table_;
}