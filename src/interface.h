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
  constexpr int min_value = (int)T::kMinValue;
  constexpr int max_value = (int)T::kMaxValue;
  std::string text;
  bool go_on = true;
  while (true)
  {
    fmt::print("Selecciona una de las siguientes opciones:\n");
    for (auto i = 1; i < max_value; i++)
    {
      fmt::print("{}. {}\n", i, TypeToString((T)i));
    }
    getline(std::cin, text);
    try
    {
      auto value = stoi(text);
      if (value > min_value && value < max_value)
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