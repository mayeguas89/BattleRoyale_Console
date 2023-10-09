#pragma once

#include "character.h"
#include "classes/class.h"
#include "data_base.h"
#include "dice.h"
#include "player.h"
#include "spell_data_base.h"
#include "weapon_data_base.h"
#include "wear_armor_data_base.h"

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
  enum class GameMode
  {
    Manual = 0,
    Automatic,
    None
  };

  static const int kMinNumPlayers = 1;
  static const int kMaxNumPlayers = 100;

  static GameManager& Get();

  bool ReadDB();

  void StartGame();

  bool IsRunning()
  {
    return is_running_;
  }

  WeaponDataBase& GetWeaponDB()
  {
    return wp_db_;
  }

  SpellDataBase& GetSpellDB()
  {
    return spell_db_;
  }

  WearArmorDataBase& GetArmorDB()
  {
    return wear_armor_db_;
  }

  void SetMode(GameMode mode)
  {
    mode_ = mode;
  }

  GameMode GetMode(void)
  {
    return mode_;
  }

  void AddPlayer(std::unique_ptr<Player>);

  Player& GetWinner();

  void EquipCharacter(Character* character, Class::Type class_type);

  GameManager(GameManager const&) = delete;

  void operator=(GameManager const&) = delete;

private:
  GameManager();
  int GetPlayersAlive();
  std::vector<std::unique_ptr<Player>> players_;
  bool is_running_ = false;
  Dice dice6_;
  std::mt19937 rng_;
  Player winner_;

  WeaponDataBase wp_db_;
  SpellDataBase spell_db_;
  WearArmorDataBase wear_armor_db_;

  GameMode mode_{GameMode::None};
};

std::string TypeToString(GameManager::GameMode mode);