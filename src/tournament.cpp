#include "tournament.h"

#include <fmt/printf.h>

#include <assert.h>

Tournament::Tournament(std::vector<Player>& players): players_{players}
{
  std::random_device dev;
  rng_ = std::mt19937(dev());

  assert(players.size() > 0);
  if (players.size() == 1)
  {
    winner_ = &players.front();
  }
  else
  {
    int number_of_rounds = std::ceil(std::log2(players_.size()));
    auto number_of_dummy_players = std::pow(2, number_of_rounds) - players_.size();
    // Vamos a situar a los dummy players al principio y al final para repartir el paso de ronda
    // Estos player tienen ataque 0 y salud 0 para que el ganador del match sea automaticamente el jugador
    for (int i = 0; i < number_of_dummy_players; i++)
    {
      auto p = Player(Player::Type::kType1);
      players_.push_back(p);
    }

    std::shuffle(players_.begin(), players_.end(), rng_);

    for (auto& player: players_)
    {
      fmt::print("{}\n", player);
    }

    for (int i = 0; i + 1 < players_.size(); i = i + 2)
    {
      auto m = Match(players_.at(i), players_.at(i + 1));
      matches_.push(m);
    }
  }
}

Player& Tournament::operator()()
{
  while (!matches_.empty())
  {
    auto& match_one = matches_.front();
    auto& winner_one = match_one();
    matches_.pop();

    if (matches_.empty())
    {
      winner_ = &winner_one;
      break;
    }

    auto& match_two = matches_.front();
    auto& winner_two = match_two();
    matches_.pop();

    matches_.push(Match(winner_one, winner_two));
  }

  return *winner_;
}

Tournament::Match::Match(Player& p_one, Player& p_two): player_one_{p_one}, player_two_{p_two} {}

Player& Tournament::Match::operator()()
{
  fmt::print("{} vs {}\n", player_one_.GetName(), player_two_.GetName());
  return player_one_;
}
