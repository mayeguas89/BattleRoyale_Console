#include "game_manager.h"

#include "fmt/format.h"

#include <iostream>
#include <string>
#include <utility>

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

  fmt::print("\n** El order de los jugadores **\n");

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
}

void GameManager::AddPlayer(const Player& p)
{
  if (players_.size() >= kMaxNumPlayers)
    return;
  players_.push_back(p);
}

void GameManager::PlayRound()
{
  static int round = 0;
  fmt::print("\n\t**Round {}**\n", round);
  auto dist = std::uniform_int_distribution<std::mt19937::result_type>(0, players_.size() - 1);

  for (size_t i = 0; i < players_.size(); i++)
  {
    auto& player = players_.at(i);
    fmt::print("Player {} turn\n", i);

    if (player.IsDead())
      continue;

    auto enemy_index = dist(rng_);

    while (enemy_index == i)
      enemy_index = dist(rng_);

    auto& enemy = players_.at(enemy_index);
    auto action = player.PlayRound();
    switch (action)
    {
      case Player::Action::kHeal:
      {
        fmt::print("Player {} se cura a si mismo\n", i);
        player.Heal();
        break;
      }
      case Player::Action::kAttack:
      {
        fmt::print("Player {} attacks with power {} to player {}\n", i, player.GetAttack(), enemy_index);
        enemy.ReceiveDamage(player.GetAttack());
        break;
      }

      default:
        break;
    }
    if (GetPlayersAlive() == 1)
      break;
  }

  fmt::print("\n**Player State**\n");
  PrintPlayers();

  auto remove_player = [](auto player) { return player.IsDead(); };
  players_.erase(std::remove_if(players_.begin(), players_.end(), remove_player), players_.end());

  if (GetPlayersAlive() == 1)
    is_running_ = false;

  round++;
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

Player& GameManager::GetWinner()
{
  return players_.at(0);
}