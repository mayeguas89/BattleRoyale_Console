#pragma once

#include "character.h"

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>

class Player
{
public:
  Player() = default;

  Player(const Player& other): character_{std::make_unique<Character>(*other.character_)} {}

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

private:
  std::unique_ptr<Character> character_;
  std::string name_;
};

inline std::ostream& operator<<(std::ostream& os, const Player& p)
{
  return os << fmt::format("{{name: {}}}", p.name_);
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
    return format_to(ctx.out(), "{{name: {}}}", p.GetName());
  }
};