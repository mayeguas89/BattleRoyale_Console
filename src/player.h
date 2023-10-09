#pragma once

#include "character.h"

#include <fmt/format.h>
#include <tabulate/table.hpp>

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
    stats_table_ = other.stats_table_;
  }

  Player& operator=(const Player& other)
  {
    character_ = std::make_unique<Character>(*other.character_);
    name_ = other.name_;
    stats_table_ = other.stats_table_;
    return *this;
  }

  Player(std::unique_ptr<Character> character, const std::string& name = "Empty"):
    character_{std::move(character)},
    name_{name}
  {
    stats_table_.add_row({"Current Health", "State"});
    stats_table_.add_row({"", ""});
  }

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

  tabulate::Table GetStatsTable()
  {
    if (character_)
    {
      character_->SetStatsTable(stats_table_);
    }
    return stats_table_;
  }

  void LevelUp()
  {
    if (character_)
    {
      character_->LevelUp();
      character_->SetStatsTable(stats_table_);
      character_->PrintAbilities();
      // stats_table_.add_row({character_->GetAbilitiesTable()});
    }
  }

  tabulate::Table GetAbilitiesTable()
  {
    if (character_)
    {
      return character_->GetAbilitiesTable();
    }
    return tabulate::Table();
  }

  void Restore()
  {
    if (character_)
      character_->Restore();
  }

private:
  std::unique_ptr<Character> character_;
  std::string name_;
  tabulate::Table stats_table_;
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