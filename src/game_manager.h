#pragma once

#include "dice.h"
#include "player.h"

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
  static const int kMaxNumPlayers = 5;

  static GameManager& GetInstance();

  static void SelectTurnOrder();

  static void StartGame();

  static std::vector<Player>& GetPlayers()
  {
    return players_;
  }

  static bool IsRunning()
  {
    return is_running_;
  }

  static void AddPlayer(const Player& player);
  static void PlayRound();

private:
  GameManager()
  {
    std::random_device dev;
    rng_ = std::mt19937(dev());
  }
  static int GetPlayersAlive();
  static std::vector<Player> players_;
  static bool is_running_;
  static Dice dice6_;

  static std::mt19937 rng_;
  static std::uniform_int_distribution<std::mt19937::result_type> dist_;

  static void PrintPlayers();
};
