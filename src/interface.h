#include <fmt/format.h>

#include <iostream>
#include <string>

namespace GameInterface
{
int GetNumberOfPlayers(std::istream& in);

std::string GetPlayerName(std::istream& in);

void InitializePlayers(std::istream& in, int num_players);

template<typename T>
T SelectFromType()
{
  constexpr int min_value = 0;
  constexpr int max_value = (int)T::None;
  std::string text;
  bool go_on = true;
  while (true)
  {
    fmt::print("Selecciona una de las siguientes opciones:\n");
    for (auto i = 0; i < max_value; i++)
    {
      fmt::print("{}. {}\n", i+1, TypeToString((T)i));
    }
    getline(std::cin, text);
    try
    {
      auto value = stoi(text);
      value--;
      if (value >= min_value && value < max_value)
        return (T)value;
      else
        fmt::print("Error al introducir la opcion,"
                   " tiene que ser un numero entre 1 y {}\n",
                   max_value-1);
    }
    catch (const std::invalid_argument&)
    {
      fmt::print("Error conviertiendo {} a un numero entero, intentalo otra vez!\n", text);
    }
  }
}


}