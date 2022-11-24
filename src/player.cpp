#include "player.h"

const float Player::kDefaultLife = 10.f;
const float Player::kDefaultAttack = 5.f;
const float Player::kDefaultHealAmount = 1.f;

Player::Player(Player::Type type, const std::string& name):
  type_{type},
  name_{name},
  current_health_{kDefaultLife},
  attack_{kDefaultAttack},
  heal_amount_{kDefaultHealAmount}
{}

std::string PlayerTypeToString(const Player::Type& type)
{
  using Type = Player::Type;
  switch (type)
  {
    case Type::kType1:
      return "kType1";
    case Type::kType2:
      return "kType2";
    case Type::kType3:
      return "kType3";
    case Type::kType4:
      return "kType4";
    default:
      return "invalid type";
  }
}