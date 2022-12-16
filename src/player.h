#pragma once

#include "character.h"

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

enum class TurnActionType
{
  Attack = 0,
  CastASpell,
  Dodge,
  UseAnObject,
  None
};

class Player
{
public:
  Player(): name_{"dummy"}, character_{nullptr} {}

  Player(const Player& other): name_{other.name_}
  {
    if (other.character_)
      character_ = std::make_unique<Character>(*other.character_);
    else
      character_ = nullptr;
  }

  Player& operator=(const Player& other)
  {
    if (other.character_)
      character_ = std::make_unique<Character>(*other.character_);
    else
      character_ = nullptr;
    name_ = other.name_;
    return *this;
  }

  Player(std::unique_ptr<Character> character, const std::string& name = "Empty"):
    character_{std::move(character)},
    name_{name}
  {}

  std::string GetName() const
  {
    return name_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Player& p);

  std::optional<Character> GetCharacter() const
  {
    if (character_)
      return *character_;
    return std::nullopt;
  }

  TurnActionType DoAction()
  {
    // if (character_)
    //   return character_->DoAction();
    return TurnActionType::None;
  }

  bool IsAlive() const
  {
    if (character_)
      return character_->IsAlive();
    return false;
  }

  std::optional<Spell> GetSpell()
  {
    if (character_)
      return character_->GetSpell();
  }

  int GetAttackModifier()
  {
    if (character_)
      return character_->GetAttackModifier();
    return 0;
  }

  int GetArmorClass()
  {
    if (character_)
      return character_->GetArmorClass();
    return 0;
  }

  int RollDamage()
  {
    if (character_)
      return character_->RollDamage();
    return 0;
  }

  void ReceiveDamage(int damage)
  {
    if (character_)
      character_->ReceiveDamage(damage);
  }

  int GetDifficultyClass()
  {
    if (character_)
      return character_->GetDifficultyClass();
    return 0;
  }

  int SavingThrows(AbilityType ability_type)
  {
    if (character_)
      return character_->SavingThrows(ability_type);
    return 0;
  }

private:
  std::unique_ptr<Character> character_ = nullptr;
  std::string name_;
};

inline std::ostream& operator<<(std::ostream& os, const Player& p)
{
  return os << fmt::format("name: {}", p.GetName()) << *p.character_ << std::endl;
  // return os << "name: " << p.GetName() << std::endl;
}

template<>
struct fmt::formatter<Player>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const Player& p, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{name: {}}}", p.GetName());
    if (p.GetCharacter())
      desc = fmt::format("{{name: {}, character: {}}}", p.GetName(), *p.GetCharacter());

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};