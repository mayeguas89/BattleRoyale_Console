#include "game_manager.h"
#include "interface.h"

#include <iostream>

int main(int, char**)
{
  auto gm = GameManager::GetInstance();
  std::cout << "Vamos a empezar el juego!\n";
  auto num_players = GameInterface::GetNumberOfPlayers(std::cin);
  GameInterface::InitializePlayers(std::cin, num_players);
  gm.StartGame();
  while (gm.IsRunning())
  {
    gm.PlayRound();
  }
  // game_manager.StartGame();
}
