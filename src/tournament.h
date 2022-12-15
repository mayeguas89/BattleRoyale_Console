#pragma once

#include "player.h"

#include <functional>
#include <memory>
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
    Match(std::pair<Player, Player> players);

    Player operator()();

  private:
    Player player_one_;
    Player player_two_;
  };

public:
  Tournament(std::vector<Player>& players);
  Player operator()();

private:
  std::queue<Match> matches_;

  Player winner_;
  std::mt19937 rng_;
};