#include "player.h"

const float Player::kDefaultLife = 10.f;
const float Player::kDefaultAttack = 2.f;
const float Player::kDefaultHealAmount = 1.f;

Player::Player(Player::Type type, const std::string& name):
  type_{type},
  name_{name},
  current_health_{kDefaultLife},
  attack_{kDefaultAttack},
  heal_amount_{kDefaultHealAmount}
{}

std::string TypeToString(const Player::Type& type)
{
  using Type = Player::Type;
  switch (type)
  {
    case Type::kType1:
      return "Type1";
    case Type::kType2:
      return "Type2";
    case Type::kType3:
      return "Type3";
    case Type::kType4:
      return "Type4";
    default:
      return "invalid type";
  }
}

std::string TypeToString(const Player::Action& action)
{
  using Action = Player::Action;
  switch (action)
  {
    case Action::kHeal:
      return "Heal";
    case Action::kAttack:
      return "Attack";
    default:
      return "invalid action";
  }
}

std::string TypeToString(const Player::Weapon& weapon)
{
  using Weapon = Player::Weapon;
  switch (weapon)
  {
    case Weapon::kSword:
      return "Sword";
    case Weapon::kArch:
      return "Arch";
    default:
      return "invalid weapon";
  }
}