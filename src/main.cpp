#include "game_manager.h"
#include "interface.h"
#include "weapon_data_base.h"

#include <tabulate/table.hpp>

#include <iostream>
int main(int, char**)
{
  // tabulate::Table weapon_table;
  // weapon_table.add_row({"Name", "Damage"});
  // WeaponDataBase weapon_db;
  // weapon_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
  //                    "simpleRangedWeapons.json",
  //                    "C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
  //                    "simpleMeleeWeapons.json"});
  // auto weapons = weapon_db.GetData();
  // for (const auto& weapon: weapons)
  // {
  //   weapon_table.add_row({weapon->GetName(), fmt::format("{}d{}", weapon->GetNumDices(), weapon->GetFaces())});
  // }

  // weapon_table.format()
  //   .font_style({tabulate::FontStyle::bold})
  //   .border_top(" ")
  //   .border_bottom(" ")
  //   .border_left(" ")
  //   .border_right(" ")
  //   .corner(" ");
  // weapon_table[0]
  //   .format()
  //   .padding_top(1)
  //   .padding_bottom(1)
  //   .font_align(tabulate::FontAlign::center)
  //   .font_style({tabulate::FontStyle::underline})
  //   .font_background_color(tabulate::Color::red);
  // weapon_table.column(1).format().font_color(tabulate::Color::yellow);
  // weapon_table[0][1].format().font_background_color(tabulate::Color::blue).font_color(tabulate::Color::white);

  // std::cout << weapon_table << std::endl;

  auto gm = GameManager::GetInstance();
  std::cout << "Vamos a empezar el juego!\n";
  auto num_players = GameInterface::GetNumberOfPlayers(std::cin);
  GameInterface::InitializePlayers(std::cin, num_players);
  gm.StartGame();
  while (gm.IsRunning())
  {
    gm.PlayRound();
  }
}
