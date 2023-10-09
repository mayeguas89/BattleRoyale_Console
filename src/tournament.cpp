#include "tournament.h"

#include "game_manager.h"
#include "turn_action.h"

#include <fmt/printf.h>
#include <tabulate/table.hpp>

#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using DataCell = std::variant<std::string, const char*, Table>;

Tournament::Tournament(const std::vector<std::unique_ptr<Player>>& players)
{
  std::vector<Player*> players_copy;
  for (auto& player: players)
  {
    players_copy.push_back(player.get());
  }
  std::random_device dev;
  rng_ = std::mt19937(dev());

  assert(players.size() > 0);
  if (players.size() == 1)
  {
    winner_ = *players.at(0);
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

    InitTable(number_of_rounds, players_copy);

    CreateMatchesQueue(players_copy);

    PrintTournamentTable();

    system("Pause");
  }
}

/**
 * @brief Ejecuta todos las eliminatorias hasta que solo queda un ganador
 * 
 * @return std::unique_ptr<Player> Ganador de la partida
 */
Player Tournament::operator()()
{
  int num_matches = (int)matches_.size();
  int round = 1;
  int round_counter = 1;
  while (!matches_.empty())
  {
    if (round_counter > num_matches)
    {
      round_counter = 1;
      num_matches = num_matches / 2;
      round++;
    }

    auto& match_one = matches_.front();
    auto winner_one = match_one();
    matches_.pop();

    if (winner_one)
    {
      tournament_table_[round_counter][round].set_text({winner_one->GetName()});
    }
    else
    {
      tournament_table_[round_counter][round].set_text({"PlayerDummy"});
    }

    round_counter++;

    if (matches_.empty())
    {
      winner_ = *winner_one;

      PrintTournamentTable();

      break;
    }

    auto& match_two = matches_.front();
    auto winner_two = match_two();
    matches_.pop();

    if (winner_two)
    {
      tournament_table_[round_counter][round].set_text({winner_two->GetName()});
    }
    else
    {
      tournament_table_[round_counter][round].set_text({"PlayerDummy"});
    }

    round_counter++;

    matches_.push(Match(std::make_pair(winner_one, winner_two)));

    PrintTournamentTable();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return winner_;
}

void Tournament::PrintTournamentTable()
{
  Table table;
  table.add_row({"TOURNAMENT TABLE"});
  table[0].format().font_background_color(tabulate::Color::green).font_align(tabulate::FontAlign::center);
  table.add_row({tournament_table_});
  std::cout << "\n" << table << "\n";
}

void Tournament::InitTable(int number_of_rounds, const std::vector<Player*>& players_copy)
{
  tournament_table_ = Table();
  std::vector<DataCell> data(number_of_rounds + 1);
  int counter = 0;
  std::generate(data.begin(), data.end(), [&counter]() { return fmt::format("Round - {}", ++counter); });
  tournament_table_.add_row(data);
  std::fill(data.begin(), data.end(), " ");

  for (size_t i = 0; i < players_copy.size(); i++)
  {
    tournament_table_.add_row(data);
  }
}

void Tournament::CreateMatchesQueue(const std::vector<Player*>& players_copy)
{
  // Creamos la cola de enfrentamientos entre cada dos jugadores
  for (int i = 0; i + 1 < players_copy.size(); i = i + 2)
  {
    if (players_copy.at(i))
      tournament_table_[i + 1][0].set_text(players_copy.at(i)->GetName());
    else
      tournament_table_[i + 1][0].set_text("PlayerDummy");

    if (players_copy.at(i + 1))
      tournament_table_[i + 2][0].set_text(players_copy.at(i + 1)->GetName());
    else
      tournament_table_[i + 2][0].set_text("PlayerDummy");

    auto m = Match(std::make_pair(players_copy.at(i), players_copy.at(i + 1)));
    matches_.push(m);
  }
}

Tournament::Match::Match(std::pair<Player*, Player*> players):
  player_one_{players.first},
  player_two_{players.second}
{}

/**
 * @brief Ejecuta la partida entre dos jugadores
 * 
 * @return Player* 
 */
Player* Tournament::Match::operator()()
{
  system("cls");

  if (!player_one_ && !player_two_)
    return nullptr;

  if (player_one_ && player_two_)
  {
    int counter = 0;
    while (player_one_->IsAlive() && player_two_->IsAlive())
    {
      tabulate::Table round_tabulate;
      round_tabulate.format().font_align(tabulate::FontAlign::center).width(60);
      round_tabulate.add_row({fmt::format("{} vs {}", player_one_->GetName(), player_two_->GetName())});
      round_tabulate[0].format().font_background_color(tabulate::Color::green);
      round_tabulate.add_row({fmt::format("Turno {}", counter + 1)});
      round_tabulate[1].format().font_background_color(tabulate::Color::yellow);
      round_tabulate.add_row({fmt::format("Turno de {}", player_one_->GetName())});

      DoTurn(player_one_, player_two_, round_tabulate);

      round_tabulate.add_row({fmt::format("Turno de {}", player_two_->GetName())});

      DoTurn(player_two_, player_one_, round_tabulate);

      round_tabulate.add_row({player_one_->GetStatsTable()});
      round_tabulate.add_row({player_two_->GetStatsTable()});

      std::cout << round_tabulate << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      system("cls");
      counter++;
    }

    auto winner = (player_one_->IsAlive()) ? player_one_ : player_two_;
    tabulate::Table winner_table;
    winner_table.add_row({fmt::format("Winner {}", winner->GetName())});
    winner_table[0].format().background_color(tabulate::Color::green);
    std::cout << winner_table << std::endl;

    winner->LevelUp();

    winner->Restore();

    return winner;
  }
  else if (player_one_)
  {
    tabulate::Table round_tabulate;
    round_tabulate.add_row({fmt::format("{} vs Dummy", player_one_->GetName())});
    round_tabulate.add_row({fmt::format("Winner {}", player_one_->GetName())});
    std::cout << round_tabulate << std::endl;
    return player_one_;
  }

  tabulate::Table round_tabulate;
  round_tabulate.add_row({fmt::format("Dummy vs {}", player_two_->GetName())});
  round_tabulate.add_row({fmt::format("Winner {}", player_two_->GetName())});
  std::cout << round_tabulate << std::endl;
  return player_two_;
}

void Tournament::Match::DoTurn(Player* performer, Player* target, Table& round_table)
{
  Table turn_table;
  auto action = performer->DoAction();
  turn_table.add_row({"Action", TurnActionTypeToString(action)});
  round_table.add_row({turn_table});
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