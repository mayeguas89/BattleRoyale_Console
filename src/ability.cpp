#include "ability.h"

Abilities::Abilities():
  map_{std::unordered_map<Ability::Type, Ability>{{Ability::Type::Strength, Ability()},
                                                  {Ability::Type::Charisma, Ability()},
                                                  {Ability::Type::Constitution, Ability()},
                                                  {Ability::Type::Dexterity, Ability()},
                                                  {Ability::Type::Intelligence, Ability()},
                                                  {Ability::Type::Wisdom, Ability()}}}
{
  abilities_table_.format().font_align(tabulate::FontAlign::center);
  abilities_table_.add_row({"Name", "Value", "Modifier"});
  for (auto it = map_.begin(); it != map_.end(); it++)
  {
    abilities_table_.add_row({AbilityTypeToString(it->first),
                              fmt::format("{}", it->second.GetScore()),
                              fmt::format("{}", it->second.GetModifier())});
  }
  SetAbilitiesTable();
}

void Abilities::SetAbilitiesTable()
{
  int counter = 1;
  for (auto it = map_.begin(); it != map_.end(); it++)
  {
    abilities_table_[counter][0].set_text({AbilityTypeToString(it->first)});
    abilities_table_[counter][1].set_text({fmt::format("{}", it->second.GetScore())});
    abilities_table_[counter][2].set_text({fmt::format("{}", it->second.GetModifier())});
    counter++;
  }
}