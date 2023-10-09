#pragma once

#include "player.h"

#include <tabulate/table.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using namespace tabulate;

class Tournament
{
  class Match
  {
  public:
    Match(std::pair<Player*, Player*> players);

    void DoTurn(Player* performer, Player* target, Table& round_table);

    Player* operator()();

  private:
    Player* player_one_;
    Player* player_two_;
  };

public:
  Tournament(const std::vector<std::unique_ptr<Player>>& players);
  Player operator()();

private:
  void InitTable(int number_of_rounds, const std::vector<Player *>& players_copy);
  void CreateMatchesQueue(const std::vector<Player *>& players_copy);
  void PrintTournamentTable();
  std::queue<Match> matches_;

  Player winner_;
  std::mt19937 rng_;

  Table tournament_table_;
};