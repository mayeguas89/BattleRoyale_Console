#include "game_manager.h"

#include "fmt/format.h"

#include <iostream>
#include <string>
#include <utility>

bool GameManager::is_running_ = false;
std::vector<Player> GameManager::players_ = std::vector<Player>();
Dice GameManager::dice6_ = Dice(6);
std::uniform_int_distribution<std::mt19937::result_type> GameManager::dist_ =
  std::uniform_int_distribution<std::mt19937::result_type>(1, GameManager::kMaxNumPlayers);
std::mt19937 GameManager::rng_ = std::mt19937();
using namespace std;

GameManager& GameManager::GetInstance()
{
  static GameManager instance;
  return instance;
}

void GameManager::SelectTurnOrder()
{
  using PlayerDiceResult = std::pair<Player, int>;
  std::vector<PlayerDiceResult> results;

  auto sort_by_result = [](const PlayerDiceResult& pair_a, const PlayerDiceResult& pair_b)
  { return pair_a.second > pair_b.second; };

  cout << "Cada jugador lanza un dado para determinar el orden de los turnos\n";

  for (size_t i = 0; i < players_.size(); i++)
  {
    // Player tira un dado
    auto res = dice6_.ThrowDice();
    fmt::print("Player {} saca un {}\n", players_.at(i).GetName(), res);
    auto pair = std::make_pair(players_.at(i), res);
    results.push_back(pair);
  }

  // Ordena por resultado de dado de mayor a menor,
  // TODO volver a lanzar si se empatan entre jugadores
  std::sort(results.begin(), results.end(), sort_by_result);
  std::vector<Player> sorted_players;
  for (auto& result: results)
  {
    sorted_players.push_back(result.first);
    fmt::print("Player: {}, result: {}\n", result.first, result.second);
  }
  std::swap(sorted_players, players_);
}

void GameManager::StartGame()
{
  SelectTurnOrder();
  is_running_ = true;
  dist_ = std::uniform_int_distribution<std::mt19937::result_type>(1, players_.size() - 1);
}

void GameManager::AddPlayer(const Player& p)
{
  if (players_.size() >= kMaxNumPlayers)
    return;
  players_.push_back(p);
}

void GameManager::PlayRound()
{
  for (size_t i = 0; i < players_.size(); i++)
  {
    auto& player = players_.at(i);
    if (player.IsDead())
      continue;
    auto enemy_index = dist_(rng_);
    while (enemy_index == i || players_.at(enemy_index).IsDead())
      enemy_index = dist_(rng_);
    auto& enemy = players_.at(enemy_index);

    auto action = player.PlayRound();
    switch (action)
    {
      case Player::Action::kHeal:
      {
        player.Heal();
        break;
      }
      case Player::Action::kAttack:
      {
        fmt::print("Player {} attacks with power {} to player {}\n",
                   player.GetName(),
                   player.GetAttack(),
                   enemy.GetName());
        enemy.ReceiveDamage(player.GetAttack());
        break;
      }

      default:
        break;
    }
    if (GetPlayersAlive() == 1)
      break;
  }
  PrintPlayers();

  if (GetPlayersAlive() == 1)
    is_running_ = false;
}

int GameManager::GetPlayersAlive()
{
  return std::count_if(players_.begin(), players_.end(), [](auto& player) { return !player.IsDead(); });
}

void GameManager::PrintPlayers()
{
  for (auto& player: players_)
  {
    fmt::print("{}\n", player);
  }
}