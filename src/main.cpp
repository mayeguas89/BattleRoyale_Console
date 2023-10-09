#include "game_manager.h"
#include "interface.h"
#include "weapon_data_base.h"

#include <tabulate/table.hpp>

#include <iostream>

int main(int argc, char const* argv[])
{
  if (!GameManager::Get().ReadDB())
    return -1;

  system("cls");
  
  std::cout <<
    R"(
    ------------------------------------------------------------------------            
            ______       _   _   _     ______                  _      
            | ___ \     | | | | | |    | ___ \                | |     
            | |_/ / __ _| |_| |_| | ___| |_/ /___  _   _  __ _| | ___ 
            | ___ \/ _` | __| __| |/ _ \    // _ \| | | |/ _` | |/ _ \
            | |_/ / (_| | |_| |_| |  __/ |\ \ (_) | |_| | (_| | |  __/
            \____/ \__,_|\__|\__|_|\___\_| \_\___/ \__, |\__,_|_|\___|
                                                    __/ |             
                                                   |___/              
    ------------------------------------------------------------------------        
    )" << std::endl;

  std::cout << "\n\nVamos a empezar el juego!\n\n";
  auto num_players = GameInterface::GetNumberOfPlayers(std::cin);
  GameInterface::SelectMode();

  GameInterface::InitializePlayers(std::cin, num_players);
  system("pause");
  GameManager::Get().StartGame();
  auto winner = GameManager::Get().GetWinner();
  tabulate::Table winner_table;

  // Global styling
  winner_table.format().font_style({tabulate::FontStyle::bold}).font_align(tabulate::FontAlign::center).width(60);
  winner_table.add_row({"Winner"});
  winner_table.add_row({fmt::format("{}", winner.GetName())});
  winner_table.add_row({winner.GetAbilitiesTable()});
  std::cout << winner_table << std::endl;
}
