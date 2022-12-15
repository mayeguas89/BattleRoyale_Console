
#pragma once

#include <unordered_map>

class Ability
{
public:
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

void operator+=(Ability& ability, int value)
{
  ability.score_ += value;
  ability.CalculateModifier();
}

struct Abilities
{
  std::unordered_map<Ability::Type, Ability> map;
  Abilities():
    map{std::unordered_map<Ability::Type, Ability>{{Ability::Type::Strength, Ability()},
                                                   {Ability::Type::Charisma, Ability()},
                                                   {Ability::Type::Constitution, Ability()},
                                                   {Ability::Type::Dexterity, Ability()},
                                                   {Ability::Type::Intelligence, Ability()},
                                                   {Ability::Type::Wisdom, Ability()}}}
  {}
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