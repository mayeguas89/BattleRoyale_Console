
#pragma once

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
    Charisma
  };

  Ability(): score_{0}, modifier_{0} {}
  Ability(int p_value): score_{p_value}
  {
    CalculateModifier();
  }
  friend void operator+=(Ability& ability, int value);

  int GetModifier()
  {
    return modifier_;
  }

  int GetScore()
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