#include "interface.h"

#include "classes/factory.h"
#include "game_manager.h"
#include "races/factory.h"

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
    std::string player_name = GetPlayerName(in);
    fmt::print("** Seleccion de character **\n");

    fmt::print("** Elige tu clase **\n");

    auto class_type = SelectFromType<Class::Type>();

    fmt::print("Has elegido {}\n", TypeToString(class_type));

    Subclass subclass_type = std::monostate{};
    switch (class_type)
    {
      case Class::Type::Cleric:

        fmt::print("** Elige tu subclase **\n");
        subclass_type = SelectFromType<Cleric::Type>();
        fmt::print("Has elegido {}\n", TypeToString(subclass_type));
        break;
      case Class::Type::Sorcerer:
        fmt::print("** Elige tu subclase **\n");
        subclass_type = SelectFromType<Sorcerer::Type>();
        fmt::print("Has elegido {}\n", TypeToString(subclass_type));
        break;
      case Class::Type::Warlock:
        fmt::print("** Elige tu subclase **\n");
        subclass_type = SelectFromType<Warlock::Type>();
        fmt::print("Has elegido {}\n", TypeToString(subclass_type));
        break;
      default:
        break;
    }

    Abilities abilities;
    auto the_class = ClassFactory::Create(abilities, class_type, subclass_type);

    fmt::print("** Elige tu raza **\n");
    auto race_type = SelectFromType<Race::Type>();
    Subrace subrace_type = std::monostate{};
    fmt::print("** Elige tu subraza **\n");
    auto race = RaceFactory::Create(abilities, race_type, subrace_type);

    auto character = std::make_unique<Character>(abilities, std::move(race), std::move(the_class));

    auto p = Player{std::move(character), player_name};
    gm.AddPlayer(p);
    fmt::print("Player {} se une al juego...\n", p);
    std::cout << abilities;
  }
}
}