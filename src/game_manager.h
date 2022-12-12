#pragma once

#include "dice.h"
#include "player.h"

#include <optional>
#include <random>
#include <vector>

// struct Round
// {
//   Player& player;
//   int order;
// }

class GameManager
{
public:
  static const int kMinNumPlayers = 1;
  static const int kMaxNumPlayers = 41;

  static GameManager& GetInstance();

  void SelectTurnOrder();
  void EnsambleMatches();

  void StartGame();

  std::vector<Player>& GetPlayers()
  {
    return players_;
  }

  bool IsRunning()
  {
    return is_running_;
  }

  void AddPlayer(const Player& player);
  void PlayRound();
  Player& GetWinner();
  void PrintPlayers();
  void ClearPlayers()
  {
    players_.clear();
  }

private:
  GameManager(): dice6_{Dice(6)}
  {
    std::random_device dev;
    rng_ = std::mt19937(dev());
  }
  int GetPlayersAlive();
  std::vector<Player> players_;
  bool is_running_ = false;
  Dice dice6_;
  std::mt19937 rng_;
};
