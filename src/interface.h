#include <iostream>
#include <string>

namespace GameInterface
{
int GetNumberOfPlayers(std::istream& in);

std::string GetPlayerName(std::istream& in);

void InitializePlayers(std::istream& in, int num_players);
}