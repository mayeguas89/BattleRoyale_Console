#include "tournament.h"

#include "turn_action.h"

#include <fmt/printf.h>
#include <tabulate/table.hpp>

#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

Tournament::Tournament(const std::vector<Player>& players)
{
  std::vector<Player*> players_copy;
  for (auto& player: players)
  {
    players_copy.push_back(new Player(player));
  }
  std::random_device dev;
  rng_ = std::mt19937(dev());

  assert(players.size() > 0);
  if (players.size() == 1)
  {
    winner_ = players.at(0);
  }
  else
  {
    auto number_of_rounds = static_cast<int>(std::ceil(std::log2(players.size())));
    auto number_of_dummy_players = static_cast<int>(std::pow(2, number_of_rounds) - players.size());

    // Añadimos los dummy player a la lista de jugadores para completar
    for (int i = 0; i < number_of_dummy_players; i++)
    {
      players_copy.push_back(nullptr);
    }

    // Creamos los enfrentamientos de manera aleatoria
    std::shuffle(players_copy.begin(), players_copy.end(), rng_);

    // Creamos la cola de enfrentamientos entre cada dos jugadores
    tabulate::Table tournament_table;
    for (int i = 0; i + 1 < players_copy.size(); i = i + 2)
    {
      if (players_copy.at(i))
        tournament_table.add_row({players_copy.at(i)->GetName()});
      else
        tournament_table.add_row({"PlayerDummy"});
      if (players_copy.at(i+1))
        tournament_table.add_row({players_copy.at(i + 1)->GetName()});
      else
        tournament_table.add_row({"PlayerDummy"});
      auto m = Match(std::make_pair(players_copy.at(i), players_copy.at(i + 1)));
      matches_.push(m);
    }

    // Iterate over rows in the table
    size_t index = 0;
    size_t index_two = 0;
    bool blue = false;
    for (auto& row: tournament_table)
    {
      row.format().font_style({tabulate::FontStyle::bold});

      if (index == 2)
      {
        for (auto& cell: row)
        {
          cell.format().font_background_color(tabulate::Color::blue);
        }
        ++index_two;
        if (index_two == 2)
        {
          index = 0;
          index_two = 0;
        }
      }
      else
      {
        index++;
      }
    }

    std::cout << "\n" << tournament_table << "\n";
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
      winner_ = *winner_one;
      break;
    }

    auto& match_two = matches_.front();
    auto winner_two = match_two();
    matches_.pop();

    matches_.push(Match(std::make_pair(winner_one, winner_two)));
  }

  return winner_;
}

Tournament::Match::Match(std::pair<Player*, Player*> players):
  player_one_{players.first},
  player_two_{players.second}
{}

/**
 * @brief Ejecuta la partida entre dos jugadores
 * 
 * @return Player& 
 */
Player* Tournament::Match::operator()()
{
  if (player_one_ && player_two_)
  {
    fmt::print("{} vs {}\n", player_one_->GetName(), player_two_->GetName());
    while (player_one_->IsAlive() && player_two_->IsAlive())
    {
      static int counter = 0;
      counter++;
      fmt::print("\n** Round {} **\n", counter);

      DoTurn(player_one_, player_two_);
      DoTurn(player_two_, player_one_);

      player_one_->PrintStats();
      player_two_->PrintStats();

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return (player_one_->IsAlive()) ? player_one_ : player_two_;
  }
  else if (player_one_)
  {
    fmt::print("{} vs Dummy\n", player_one_->GetName());
    return player_one_;
  }
  fmt::print("Dummy vs {}\n", player_two_->GetName());
  return player_two_;
}

void Tournament::Match::DoTurn(Player* performer, Player* target)
{
  auto action = performer->DoAction();
  fmt::print("\n** {} elige {} **\n", performer->GetName(), TurnActionTypeToString(action));
  switch (action)
  {
    case TurnActionType::Attack:
    {
      auto turn_action = AttackToTarget(performer->GetCharacter(), target->GetCharacter());
      turn_action();
      break;
    }
    case TurnActionType::CastASpell:
    {
      auto spell = performer->GetCharacter()->GetSpell();
      if (spell != nullptr)
      {
        auto turn_action = CastSpell(performer->GetCharacter(), target->GetCharacter(), spell);
        turn_action();
      }
      break;
    }
    default:
      break;
  }
}