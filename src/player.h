#pragma once

#include "character.h"

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

enum class TurnActionType;

class Player
{
public:
  // virtual ~Player() = default;
  Player() = default;

  Player(const Player& other): name_{other.name_}
  {
    character_ = std::make_unique<Character>(*other.character_);
  }

  Player& operator=(const Player& other)
  {
    character_ = std::make_unique<Character>(*other.character_);
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

  Character* GetCharacter() const
  {
    if (character_)
      return character_.get();
    return nullptr;
  }

  TurnActionType DoAction();

  bool IsAlive() const
  {
    if (character_)
      return character_->IsAlive();
    return false;
  }

  void PrintStats()
  {
    if (character_)
    {
      fmt::print("\n** {} **\n", name_);
      character_->PrintStats();
    }
  }

private:
  std::unique_ptr<Character> character_;
  std::string name_;
};

inline std::ostream& operator<<(std::ostream& os, const Player& p)
{
  os << fmt::format("name: {}", p.GetName()) << std::endl;
  return os << *p.character_ << std::endl;
}

template<>
struct fmt::formatter<Player>: fmt::formatter<std::string>
{
  template<typename FormatContext>
  auto format(const Player& p, FormatContext& ctx) const
  {
    auto desc = fmt::format("{{name: {}, character: {}}}", p.GetName(), fmt::ptr(p.GetCharacter()));

    return fmt::formatter<std::string>::format(desc, ctx);
  }
};