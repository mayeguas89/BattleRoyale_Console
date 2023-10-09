#include "game_manager.h"

#include "fmt/format.h"
#include "tournament.h"

#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
namespace fs = std::filesystem;

GameManager::GameManager(): dice6_{Dice(6)}, mode_{GameManager::GameMode::None}
{
  std::random_device dev;
  rng_ = std::mt19937(dev());
}

bool GameManager::ReadDB()
{
  char binary_path[MAX_PATH];
  GetModuleFileName(NULL, binary_path, MAX_PATH);
  fs::path path{binary_path};
  path = path.parent_path().make_preferred();
  auto ranged_weapons = path / "cfg/final_ranged_weapons.json";
  std::error_code ec;
  if(!fs::exists(ranged_weapons, ec))
  {
    std::cerr << fmt::format("Error reading file: {}\n", ranged_weapons.string());
    return false;
  }
  auto melee_weapons = path / "cfg/final_melee_weapons.json";
  if(!fs::exists(melee_weapons, ec))
  {
    std::cerr << fmt::format("Error reading file: {}\n", melee_weapons.string());
    return false;
  }
  auto armor_file = path / "cfg/final_armor.json";
  if(!fs::exists(armor_file, ec))
  {
    std::cerr << fmt::format("Error reading file: {}\n", armor_file.string());
    return false;
  }
  auto spells_file = path / "cfg/final_spells.json";
  if(!fs::exists(spells_file, ec))
  {
    std::cerr << fmt::format("Error reading file: {}\n", spells_file.string());
    return false;
  }

  wp_db_.AddData({ranged_weapons.string(), melee_weapons.string()});
  wear_armor_db_.AddData({armor_file.string()});
  spell_db_.AddData({spells_file.string()});
  return true;
}

GameManager& GameManager::Get()
{
  static GameManager instance;
  return instance;
}

void GameManager::StartGame()
{
  Tournament tournament{players_};
  winner_ = tournament();
}

void GameManager::AddPlayer(std::unique_ptr<Player> p)
{
  if (players_.size() >= kMaxNumPlayers)
    return;
  players_.push_back(std::move(p));
}

Player& GameManager::GetWinner()
{
  return winner_;
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
