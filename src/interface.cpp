#include "interface.h"

#include "game_manager.h"

#include <fmt/format.h>

using namespace std;

namespace GameInterface
{
int GetNumberOfPlayers(std::istream& in)
{
  auto gm = GameManager::GetInstance();
  string text;
  bool go_on = true;
  int num_players;
  while (go_on)
  {
    cout << "Cuantos jugadores participan en el juego?\n";
    getline(in, text);
    try
    {
      num_players = stoi(text);
      if (GameManager::kMinNumPlayers < num_players && num_players <= GameManager::kMaxNumPlayers)
        go_on = false;
      else
        fmt::print("Error al introducir el numero de jugadores,"
                   " tiene que ser un numero entre {} y {}\n",
                   GameManager::kMinNumPlayers,
                   GameManager::kMaxNumPlayers);
    }
    catch (const invalid_argument&)
    {
      fmt::print("Error conviertiendo {} a un numero entero, intentalo otra vez!\n", text);
    }
  }
  return num_players;
}

std::string GetPlayerName(std::istream& in)
{
  std::string player_name;
  cout << "Introduce el nombre del jugador:\n";
  getline(in, player_name);
  return player_name;
}

void InitializePlayers(std::istream& in, int number_players)
{
  auto gm = GameManager::GetInstance();
  string text;
  for (int n = 0; n < number_players; n++)
  {
    bool go_on = true;
    int player_type;
    std::string player_name = GetPlayerName(in);
    while (go_on)
    {
      fmt::print("Introduce el tipo de jugador\n", n + 1);
      cout << "1.Tipo 1\n";
      cout << "2.Tipo 2\n";
      cout << "3.Tipo 3\n";
      cout << "4.Tipo 4\n";
      getline(in, text);
      try
      {
        player_type = stoi(text);
        if (Player::CheckPlayerType(player_type))
          go_on = false;
        else
          fmt::print("Error al introducir el tipo de jugador,"
                     " tiene que ser un numero entre 1 y {}\n",
                     (int)Player::Type::kNumPlayerType);
      }
      catch (const invalid_argument&)
      {
        fmt::print("Error conviertiendo {} a un numero entero, intentalo otra vez!\n", text);
      }
    }

    auto p = Player{(Player::Type)player_type, player_name};
    gm.AddPlayer(p);
    fmt::print("Player {} se une al juego...\n", p);
  }
}
}