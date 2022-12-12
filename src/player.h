#pragma once

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <string>

class Player
{
public:
  static const float kDefaultLife;
  static const float kDefaultAttack;
  static const float kDefaultHealAmount;

  enum class Type
  {
    kMinValue = 0,
    kType1,
    kType2,
    kType3,
    kType4,
    kMaxValue
  };
  enum class Action
  {
    kMinValue = 0,
    kHeal,
    kAttack,
    kMaxValue
  };
  enum class Weapon
  {
    kMinValue = 0,
    kSword,
    kArch,
    kMaxValue
  };

  Player(Type type, const std::string& name = "Empty");

  Action PlayRound()
  {
    if (current_health_ < kDefaultLife / 2.f)
    {
      return Action::kHeal;
    }
    return Action::kAttack;
  }

  void Heal()
  {
    current_health_ += heal_amount_;
    if (current_health_ > kDefaultLife)
    {
      current_health_ = kDefaultLife;
    }
  }

  std::string GetName() const
  {
    return name_;
  }

  bool IsDead() const
  {
    return current_health_ <= 0.f;
  }

  float GetHealth() const
  {
    return current_health_;
  }

  float GetAttack() const
  {
    return attack_;
  }

  Type GetType() const
  {
    return type_;
  }

  void ReceiveDamage(float damage)
  {
    current_health_ -= damage;
  }

  friend std::ostream& operator<<(std::ostream& os, const Player& p);

private:
  float current_health_;
  float heal_amount_;
  float attack_;
  Type type_;
  std::string name_;
};

std::string TypeToString(const Player::Type& type);
std::string TypeToString(const Player::Action& action);
std::string TypeToString(const Player::Weapon& weapon);

inline std::ostream& operator<<(std::ostream& os, const Player& p)
{
  return os << fmt::format("{{name: {}, type: {}, health: {}, attack: {}}}",
                           p.name_,
                           TypeToString(p.type_),
                           p.current_health_,
                           p.attack_);
}

template<>
struct fmt::formatter<Player>
{
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template<typename FormatContext>
  auto format(const Player& p, FormatContext& ctx) -> decltype(ctx.out())
  {
    // ctx.out() is an output iterator to write to.
    return format_to(ctx.out(),
                     "{{name: {}, type: {}, health: {}, attack: {}}}",
                     p.GetName(),
                     TypeToString(p.GetType()),
                     p.GetHealth(),
                     p.GetAttack());
  }
};