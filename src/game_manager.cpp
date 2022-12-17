#include "game_manager.h"

#include "fmt/format.h"
#include "tournament.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <utility>


using namespace std;
namespace fs = std::filesystem;

GameManager::GameManager(): dice6_{Dice(6)}, mode_{GameManager::GameMode::None}
{
  fs::path path{"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug"};
  auto ranged_weapons = path / "cfg/final_ranged_weapons.json";
  auto melee_weapons = path / "cfg/final_melee_weapons.json";
  auto armor = path / "cfg/final_armor.json";
  auto spells = path / "cfg/final_spells.json";
  wp_db_.AddData({ranged_weapons.string(), melee_weapons.string()});
  wear_armor_db_.AddData({armor.string()});
  spell_db_.AddData({spells.string()});
  std::random_device dev;
  rng_ = std::mt19937(dev());
}

GameManager& GameManager::Get()
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

void GameManager::EnsambleMatches()
{
  std::shuffle(std::begin(players_), std::end(players_), rng_);
}

void GameManager::StartGame()
{
  EnsambleMatches();
  Tournament tournament{players_};
  auto winner = tournament();
  // is_running_ = true;
}

void GameManager::AddPlayer(const Player& p)
{
  if (players_.size() >= kMaxNumPlayers)
    return;
  players_.push_back(p);
}

void GameManager::PlayRound()
{
  // static int round = 0;
  // fmt::print("\n\t**Round {}**\n", round);
  // auto dist = std::uniform_int_distribution<std::mt19937::result_type>(0, players_.size() - 1);

  // for (size_t i = 0; i < players_.size(); i++)
  // {
  //   auto& player = players_.at(i);
  //   fmt::print("Player {} turn\n", i);

  //   if (player.IsDead())
  //     continue;

  //   auto enemy_index = dist(rng_);

  //   while (enemy_index == i)
  //     enemy_index = dist(rng_);

  //   auto& enemy = players_.at(enemy_index);
  //   auto action = player.PlayRound();
  //   switch (action)
  //   {
  //     case Player::Action::kHeal:
  //     {
  //       fmt::print("Player {} se cura a si mismo\n", i);
  //       player.Heal();
  //       break;
  //     }
  //     case Player::Action::kAttack:
  //     {
  //       fmt::print("Player {} attacks with power {} to player {}\n", i, player.GetAttack(), enemy_index);
  //       enemy.ReceiveDamage(player.GetAttack());
  //       break;
  //     }

  //     default:
  //       break;
  //   }
  //   if (GetPlayersAlive() == 1)
  //     break;
  // }

  // fmt::print("\n**Player State**\n");
  // PrintPlayers();

  // auto remove_player = [](auto player) { return player.IsDead(); };
  // players_.erase(std::remove_if(players_.begin(), players_.end(), remove_player), players_.end());

  // if (GetPlayersAlive() == 1)
  //   is_running_ = false;

  // round++;
}

int GameManager::GetPlayersAlive()
{
  // return std::count_if(players_.begin(), players_.end(), [](auto& player) { return !player.IsDead(); });
  return 0;
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

void GameManager::EquipCharacter(Character* character, Class::Type class_type)
{
  auto shield = std::make_shared<Shield>("Shield", 2);
  switch (class_type)
  {
    case Class::Type::Barbarian:
      character->EquipWeapon(wp_db_.GetDataByName("Greataxe"));
      break;
    case Class::Type::Bard:
      character->EquipWeapon(wp_db_.GetDataByName("Rapier"));
      break;
    case Class::Type::Cleric:
      character->EquipWeapon(wp_db_.GetDataByName("Mace"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Scale Mail"));
      character->EquipShield(shield);
      break;
    case Class::Type::Druid:
      character->EquipWeapon(wp_db_.GetDataByName("Scimitar"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Leather Armor"));
      character->EquipShield(shield);
      break;
    case Class::Type::Fighter:
      character->EquipWeapon(wp_db_.GetDataByName("Glaive"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Chain Mail"));
      break;
    case Class::Type::Ranger:
      character->EquipWeapon(wp_db_.GetDataByName("Barbed Dagger"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Scale Mail"));
      break;
    case Class::Type::Rogue:
      character->EquipWeapon(wp_db_.GetDataByName("Rapier"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Leather Armor"));
      break;
    case Class::Type::Sorcerer:
      character->EquipWeapon(wp_db_.GetDataByName("Brandistock"));
      break;
    case Class::Type::Warlock:
      character->EquipWeapon(wp_db_.GetDataByName("Brandistock"));
      character->EquipWearAmor(wear_armor_db_.GetDataByName("Leather Armor"));
      break;
    case Class::Type::Wizard:
      character->EquipWeapon(wp_db_.GetDataByName("Dagger"));
      break;
  }

  if (character->CanThrowSpels())
  {
    auto& sp_db = spell_db_.GetSpellsByLevel(1);
    for (int i = 0; i < character->GetNumberOfSpellsSlots(); i++)
    {
      character->EquipSpell(sp_db.at(SingletonDice::Get().Roll(static_cast<int>(sp_db.size())) - 1));
    }
  }
}

std::string TypeToString(GameManager::GameMode mode)
{
  switch (mode)
  {
    case GameManager::GameMode::Manual:
      return "Manual";
    case GameManager::GameMode::Automatic:
      return "Automatic";
  }
  return "UNDEFINED";
}
