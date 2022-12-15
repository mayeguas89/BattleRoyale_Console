#include "tournament.h"

#include <fmt/printf.h>

#include <assert.h>

Tournament::Tournament(std::vector<Player>& players)
{
  std::random_device dev;
  rng_ = std::mt19937(dev());

  assert(players.size() > 0);
  if (players.size() == 1)
  {
    winner_ = players[0];
  }
  else
  {
    int number_of_rounds = (int)std::ceil(std::log2(players.size()));
    auto number_of_dummy_players = std::pow(2, number_of_rounds) - players.size();

    // Añadimos los dummy player a la lista de jugadores para completar
    for (int i = 0; i < number_of_dummy_players; i++)
    {
      players.push_back(Player());
    }

    // Creamos los enfrentamientos de manera aleatoria
    std::shuffle(players.begin(), players.end(), rng_);

    for (const auto& player: players)
    {
      fmt::print("{}\n", player);
    }

    // Creamos la cola de enfrentamientos entre cada dos jugadores
    for (int i = 0; i + 1 < players.size(); i = i + 2)
    {
      auto m = Match(std::make_pair(players.at(i), players.at(i + 1)));
      matches_.push(m);
    }
  }
}

/**
 * @brief Ejecuta todos las eliminatorias hasta que solo queda un ganador
 * 
 * @return std::unique_ptr<Player> Ganador de la partida
 */
Player Tournament::operator()()
{
  while (!matches_.empty())
  {
    auto& match_one = matches_.front();
    auto winner_one = match_one();
    matches_.pop();

    if (matches_.empty())
    {
      winner_ = winner_one;
      break;
    }

    auto& match_two = matches_.front();
    auto winner_two = match_two();
    matches_.pop();

    matches_.push(Match(std::make_pair(winner_one, winner_two)));
  }

  return winner_;
}

Tournament::Match::Match(std::pair<Player, Player> players):
  player_one_{players.first},
  player_two_{players.second}
{}

/**
 * @brief Ejecuta la partida entre dos jugadores
 * 
 * @return Player& 
 */
Player Tournament::Match::operator()()
{
  fmt::print("{} vs {}\n", player_one_.GetName(), player_two_.GetName());
  return player_one_;
}
