#include "dice.h"
#include "game_manager.h"
#include "interface.h"
#include "tournament.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Dice, Simple)
{
  auto d = Dice(6);
  EXPECT_NE(d.ThrowDice(), d.ThrowDice());
}

TEST(GameManager, NumberOfPlayersIsNotBiggerThanMaximumAllowed)
{
  using Type = Player::Type;
  auto gm = GameManager::GetInstance();
  for (int i = 0; i <= GameManager::kMaxNumPlayers; i++)
  {
    gm.AddPlayer(Player{Type::kType1, std::to_string(i)});
  }
  ASSERT_THAT(gm.GetPlayers(), SizeIs(GameManager::kMaxNumPlayers));
}

void AddPlayersToGM(GameManager& gm, int number_of_players)
{
    for (int i = 0; i < number_of_players; i++)
  {
    gm.AddPlayer(Player{Player::Type::kType1, std::to_string(i)});
  }
}

struct TournamentTest: Test
{
  GameManager& gm = GameManager::GetInstance();
};

TEST_F(TournamentTest, TournamentOneParticipantGiveOnlyPlayerAsWinner)
{
  gm.ClearPlayers();
  AddPlayersToGM(gm, 1);

  Tournament t(gm.GetPlayers());
  auto& winner = t();
  ASSERT_EQ(winner.GetName(), "0");
  fmt::print("Player {} has win!\n", winner.GetName());
}

TEST_F(TournamentTest, TournamentOddParticipant)
{
  gm.ClearPlayers();
  AddPlayersToGM(gm, 3);

  Tournament t(gm.GetPlayers());
  auto& winner = t();
  ASSERT_EQ(winner.GetName(), "0");
  fmt::print("Player {} has win!\n", winner.GetName());
}

TEST_F(TournamentTest, TournamentEvenParticipant)
{
  gm.ClearPlayers();
  int participants = 4;
  AddPlayersToGM(gm, participants);

  Tournament t(gm.GetPlayers());
  auto& winner = t();
  ASSERT_EQ(winner.GetName(), "0");
  fmt::print("Player {} has win!\n", winner.GetName());
}

TEST_F(TournamentTest, TournamentEvenNotPowerOf2)
{
  gm.ClearPlayers();
  int participants = 6;
  AddPlayersToGM(gm, participants);

  Tournament t(gm.GetPlayers());
  auto& winner = t();
  ASSERT_EQ(winner.GetName(), "0");
  fmt::print("Player {} has win!\n", winner.GetName());
}

TEST_F(TournamentTest, TournamentEvenNotPowerOf2Two)
{
  gm.ClearPlayers();
  int participants = 12;
  AddPlayersToGM(gm, participants);

  Tournament t(gm.GetPlayers());
  auto& winner = t();
  ASSERT_EQ(winner.GetName(), "0");
  fmt::print("Player {} has win!\n", winner.GetName());
}

struct GameManagerTest: Test
{
  GameManager& gm = GameManager::GetInstance();
  GameManagerTest()
  {
    // for (int i = 0; i < GameManager::kMaxNumPlayers; i++)
    for (int i = 0; i < 5; i++)
    {
      gm.AddPlayer(Player{Player::Type::kType1, std::to_string(i)});
    }
  }
};

TEST_F(GameManagerTest, PlayRound)
{
  gm.StartGame();
  while (gm.IsRunning())
  {
    gm.PlayRound();
  }

  fmt::print("\n** Combat has finished **\n");
  auto& p = gm.GetWinner();

  fmt::print("Player {} has win!\n", p.GetName());
}

TEST(Interface, SelectFromType)
{
  GameInterface::SelectFromType<Player::Type>();
  GameInterface::SelectFromType<Player::Action>();
  GameInterface::SelectFromType<Player::Weapon>();
}
