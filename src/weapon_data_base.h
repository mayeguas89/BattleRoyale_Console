#pragma once

#include "data_base.h"
#include "nlohmann/json.hpp"
#include "weapon.h"

#include <fstream>
#include <memory>
#include <regex>
#include <unordered_map>

class WeaponDataBase: DataBase<Weapon>
{
public:
  WeaponDataBase() {}

  void AddData(const std::vector<std::string>& filenames) override
  {
    auto range_weapon_file = filenames.at(0);
    auto melee_weapon_file = filenames.at(1);

    auto ranged_weapons = Read(range_weapon_file);
    for (const auto& ranged_weapon: ranged_weapons)
    {
      weapons_[ranged_weapon.GetName()] = std::make_shared<RangedWeapon>(ranged_weapon.GetName(),
                                                                         ranged_weapon.GetNumDices(),
                                                                         ranged_weapon.GetFaces());
    }
    auto melee_weapons = Read(melee_weapon_file);
    for (const auto& melee_weapon: melee_weapons)
    {
      weapons_[melee_weapon.GetName()] =
        std::make_shared<MeleeWeapon>(melee_weapon.GetName(), melee_weapon.GetNumDices(), melee_weapon.GetFaces());
    }
  }

  std::vector<std::shared_ptr<Weapon>> GetData() override
  {
    std::vector<std::shared_ptr<Weapon>> v;
    std::transform(weapons_.begin(),
                   weapons_.end(),
                   std::back_inserter(v),
                   [](auto& item) { return item.second; });
    return v;
  }

  std::shared_ptr<Weapon> GetDataByName(const std::string& name) override
  {
    if (auto it = weapons_.find(name); it != weapons_.end())
    {
      return it->second;
    }
    return nullptr;
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Weapon>> weapons_;

  std::vector<Weapon> Read(const std::string& json_file)
  {
    std::vector<Weapon> weapons;
    std::ifstream f{json_file};
    auto data = nlohmann::json::parse(f);

    for (const auto& weapon: data)
    {
      static std::regex rx{"([0-9])d([0-9]*).*"};

      std::cmatch match;

      int num_dices;
      int faces;
      std::string s = weapon.at("Damage");
      if (std::regex_match(s.c_str(), match, rx))
      {
        num_dices = std::stoi(match[1]);
        faces = std::stoi(match[2]);
      }

      weapons.emplace_back(weapon.at("Name"), num_dices, faces);
    }
    return weapons;
  }
};