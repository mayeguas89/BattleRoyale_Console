#include "dice.h"
#include "game_manager.h"
#include "interface.h"

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

struct GameManagerTest: Test
{
  GameManager& gm = GameManager::GetInstance();
  GameManagerTest()
  {
    for (int i = 0; i < GameManager::kMaxNumPlayers; i++)
    {
      gm.AddPlayer(Player{Player::Type::kType1, std::to_string(i)});
    }
    gm.StartGame();
  }
};

TEST_F(GameManagerTest, PlayRound) 
{
  while (gm.IsRunning())
  {
    gm.PlayRound();
  }
}

TEST(Interface, SelectFromType)
{
  GameInterface::SelectFromType<Player::Type>();
  GameInterface::SelectFromType<Player::Action>();
  GameInterface::SelectFromType<Player::Weapon>();
}
