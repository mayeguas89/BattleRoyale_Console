#pragma once

#include "armor.h"
#include "data_base.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <memory>
#include <unordered_map>

class WearArmorDataBase: DataBase<WearArmor>
{
public:
  const std::string kLightArmor = "LA";
  const std::string kHeavyArmor = "HA";
  const std::string kMediumArmor = "MA";

  WearArmorDataBase() {}

  void AddData(const std::vector<std::string>& filenames) override
  {
    auto armor_file = filenames.at(0);

    auto armors = Read(armor_file);
    for (const auto& armor: armors)
    {
      armors_[armor->GetName()] = armor;
    }
  }

  std::vector<std::shared_ptr<WearArmor>> GetData() override
  {
    std::vector<std::shared_ptr<WearArmor>> v;
    std::transform(armors_.begin(), armors_.end(), std::back_inserter(v), [](auto& item) { return item.second; });
    return v;
  }

  std::shared_ptr<WearArmor> GetDataByName(const std::string& name) override
  {
    if (auto it = armors_.find(name); it != armors_.end())
    {
      return it->second;
    }
    return nullptr;
  }

private:
  std::unordered_map<std::string, std::shared_ptr<WearArmor>> armors_;

  std::vector<std::shared_ptr<WearArmor>> Read(const std::string& json_file)
  {
    std::vector<std::shared_ptr<WearArmor>> armors;
    std::ifstream f{json_file};
    auto data = nlohmann::json::parse(f);

    for (const auto& armor: data)
    {
      int ac = armor.at("ac");
      std::string name = armor.at("name");
      if (armor.at("type") == kLightArmor)
      {
        armors.push_back(std::make_shared<LightArmor>(name, ac));
      }
      else if (armor.at("type") == kHeavyArmor)
      {
        armors.push_back(std::make_shared<HeavyArmor>(name, ac));
      }
      else if (armor.at("type") == kMediumArmor)
      {
        armors.push_back(std::make_shared<MediumArmor>(name, ac));
      }
    }
    return armors;
  }
};