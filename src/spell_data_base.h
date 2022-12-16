#pragma once

#include "data_base.h"
#include "nlohmann/json.hpp"
#include "spell.h"

#include <fstream>
#include <regex>
#include <unordered_map>

class SpellDataBase: DataBase<Spell>
{
public:
  SpellDataBase() {}

  void AddData(const std::vector<std::string>& filenames) override
  {
    auto spells_file = filenames.at(0);
    auto spells = Read(spells_file);
    for (const auto& spell: spells)
    {
      spells_[spell.GetName()] = std::make_shared<Spell>(spell);
    }
  }

  std::vector<std::shared_ptr<Spell>> GetData() override
  {
    std::vector<std::shared_ptr<Spell>> v;
    std::transform(spells_.begin(), spells_.end(), std::back_inserter(v), [](auto& item) { return item.second; });
    return v;
  }

  std::shared_ptr<Spell> GetDataByName(const std::string& name) override
  {
    if (auto it = spells_.find(name); it != spells_.end())
    {
      return it->second;
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<Spell>> GetSpellsByLevel(int level)
  {
    auto data = GetData();
    std::vector<std::shared_ptr<Spell>> v;
    std::copy_if(data.begin(),
                 data.end(),
                 std::back_inserter(v),
                 [level](auto& item) { return item->GetLevel() == level; });
    return v;
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Spell>> spells_;

  std::vector<Spell> Read(const std::string& json_file)
  {
    std::vector<Spell> spells;
    std::ifstream f{json_file};
    auto data = nlohmann::json::parse(f);

    for (const auto& spell: data)
    {
      static std::regex rx{"([0-9])d([0-9]*).*"};

      std::cmatch match;

      int num_dices = 0;
      int faces = 0;
      Spell::EffectType effect_type = Spell::EffectType::Damage;
      std::string s;

      if (auto it = spell.at("data").find("Healing"); it != spell.at("data").end())
      {
        effect_type = Spell::EffectType::Healing;
        s = spell.at("data").at("Healing");
      }
      else
      {
        s = spell.at("data").at("Damage");
      }

      std::vector<Spell::DamageInflict> damage_inflict;
      for (auto& damageInflinct: spell.at("damageInflict"))
      {
        damage_inflict.push_back(StringToDamageInflict(damageInflinct));
      }

      if (std::regex_match(s.c_str(), match, rx))
      {
        num_dices = std::stoi(match[1]);
        faces = std::stoi(match[2]);

        int level = spell.at("level");
        Ability::Type saving_throw = Ability::Type::None;
        if (auto it = spell.at("data").find("Save"); it != spell.at("data").end())
          saving_throw = StringToAbilityType(spell.at("data").at("Save"));

        spells.emplace_back(spell.at("name"), num_dices, faces, level, saving_throw, damage_inflict, effect_type);
      }
    }
    return spells;
  }
};