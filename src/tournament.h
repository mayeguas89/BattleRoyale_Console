#pragma once

#include "player.h"

#include <functional>
#include <optional>
#include <queue>
#include <random>
#include <utility>
#include <vector>


class Tournament
{
  class Match
  {
  public:
    Match(Player& p_one, Player& p_two);
    Player& operator()();

  private:
    Player& player_one_;
    Player& player_two_;
  };

public:
  Tournament(std::vector<Player>& players);
  Player& operator()();

private:
  std::vector<Player>& players_;

  std::queue<Match> matches_;

  Player* winner_ = nullptr;
  std::mt19937 rng_;
};