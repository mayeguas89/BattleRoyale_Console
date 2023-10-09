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

void ManualPlayerInitialization(std::istream& in)
{
  std::string player_name = GetPlayerName(in);
  fmt::print("** Seleccion de character **\n");

  fmt::print("** Elige tu clase **\n");

  auto class_type = SelectFromType<Class::Type>();

  Subclass subclass_type = std::monostate{};
  switch (class_type)
  {
    case Class::Type::Cleric:

      fmt::print("** Elige tu subclase **\n");
      subclass_type = SelectFromType<Cleric::Type>();
      break;
    case Class::Type::Sorcerer:
      fmt::print("** Elige tu subclase **\n");
      subclass_type = SelectFromType<Sorcerer::Type>();
      break;
    case Class::Type::Warlock:
      fmt::print("** Elige tu subclase **\n");
      subclass_type = SelectFromType<Warlock::Type>();
      break;
    default:
      break;
  }

  fmt::print("Has elegido {} : {}\n", TypeToString(class_type), TypeToString(subclass_type));

  Abilities abilities;
  auto the_class = ClassFactory::Create(abilities, class_type, subclass_type);

  fmt::print("** Elige tu raza **\n");
  auto race_type = SelectFromType<Race::Type>();
  Subrace subrace_type;
  switch (race_type)
  {
    case Race::Type::Dwarf:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Dwarf::Type>();
      break;
    case Race::Type::Drow:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Drow::Type>();
      break;
    case Race::Type::Tiefling:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Tiefling::Type>();
      break;
    case Race::Type::Elf:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Elf::Type>();
      break;
    case Race::Type::HalfElf:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<HalfElf::Type>();
      break;
    case Race::Type::Halfling:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Halfling::Type>();
      break;
    case Race::Type::Gnome:
      fmt::print("** Elige tu subraza **\n");
      subrace_type = SelectFromType<Gnome::Type>();
      break;
  }

  fmt::print("Has elegido {} : {}\n", TypeToString(race_type), TypeToString(subrace_type));

  auto race = RaceFactory::Create(abilities, race_type, subrace_type);
  auto character = std::make_unique<Character>(abilities, std::move(race), std::move(the_class));
  GameManager::Get().EquipCharacter(character.get(), class_type);
  auto player = std::make_unique<Player>(std::move(character), player_name);

  std::cout << "Created player " << *player.get() << std::endl;
  std::cout << " se une al juego...\n\n";
  GameManager::Get().AddPlayer(std::move(player));
  std::cout << abilities << std::endl;
}

void AutomaticPlayerInitialization(int player_number)
{
  std::string player_name = fmt::format("Player_{}", player_number);
  auto class_type = SelectRandomEnum<Class::Type>();

  Subclass subclass_type = std::monostate{};
  switch (class_type)
  {
    case Class::Type::Cleric:
      subclass_type = SelectRandomEnum<Cleric::Type>();
      break;
    case Class::Type::Sorcerer:
      subclass_type = SelectRandomEnum<Sorcerer::Type>();
      break;
    case Class::Type::Warlock:
      subclass_type = SelectRandomEnum<Warlock::Type>();
      break;
    default:
      break;
  }
  fmt::print("Has elegido {} : {}\n", TypeToString(class_type), TypeToString(subclass_type));

  Abilities abilities;
  auto the_class = ClassFactory::Create(abilities, class_type, subclass_type);

  auto race_type = SelectRandomEnum<Race::Type>();
  Subrace subrace_type;
  switch (race_type)
  {
    case Race::Type::Dwarf:
      subrace_type = SelectRandomEnum<Dwarf::Type>();
      break;
    case Race::Type::Drow:
      subrace_type = SelectRandomEnum<Drow::Type>();
      break;
    case Race::Type::Tiefling:
      subrace_type = SelectRandomEnum<Tiefling::Type>();
      break;
    case Race::Type::Elf:
      subrace_type = SelectRandomEnum<Elf::Type>();
      break;
    case Race::Type::HalfElf:
      subrace_type = SelectRandomEnum<HalfElf::Type>();
      break;
    case Race::Type::Halfling:
      subrace_type = SelectRandomEnum<Halfling::Type>();
      break;
    case Race::Type::Gnome:
      subrace_type = SelectRandomEnum<Gnome::Type>();
      break;
  }

  fmt::print("Has elegido {} : {}\n", TypeToString(race_type), TypeToString(subrace_type));

  auto race = RaceFactory::Create(abilities, race_type, subrace_type);
  auto character = std::make_unique<Character>(abilities, std::move(race), std::move(the_class));
  GameManager::Get().EquipCharacter(character.get(), class_type);
  auto player = std::make_unique<Player>(std::move(character), player_name);

  std::cout << "Created player " << *player.get() << std::endl;
  std::cout << " se une al juego...\n\n";
  GameManager::Get().AddPlayer(std::move(player));
  std::cout << abilities << std::endl;
}

void InitializePlayers(std::istream& in, int number_players)
{
  string text;
  for (int n = 0; n < number_players; n++)
  {
    if (GameManager::Get().GetMode() == GameManager::GameMode::Manual)
    {
      ManualPlayerInitialization(in);
    }
    else
    {
      AutomaticPlayerInitialization(n);
    }
  }
}

void SelectMode()
{
  std::cout << "\n\n";
  auto mode = SelectFromType<GameManager::GameMode>();
  GameManager::Get().SetMode(mode);
}
}