#include "character.h"
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
  // GameInterface::SelectFromType<Player::Type>();
  // GameInterface::SelectFromType<Player::Action>();
  // GameInterface::SelectFromType<Player::Weapon>();
}

TEST(AbilityTest, AbilityGetScore)
{
  Ability ability(1);
  ASSERT_EQ(ability.GetModifier(), -5);

  ability.SetScore(4);
  ASSERT_EQ(ability.GetModifier(), -3);
  ability.SetScore(5);
  ASSERT_EQ(ability.GetModifier(), -3);

  ability.SetScore(10);
  ASSERT_EQ(ability.GetModifier(), 0);
  ability.SetScore(11);
  ASSERT_EQ(ability.GetModifier(), 0);

  ability.SetScore(21);
  ASSERT_EQ(ability.GetModifier(), 5);

  ability.SetScore(30);
  ASSERT_EQ(ability.GetModifier(), 10);
}

#include "race.h"

TEST(RaceTest, HumanCreation)
{
  Abilities abilities;
  auto human = RaceFactory::Create(abilities, Race::Type::Human);
  for (auto& ability: abilities.map)
  {
    ASSERT_EQ(ability.second.GetScore(), 1);
  }
}

TEST(RaceTest, GithyankiCreation)
{
  Abilities abilities;
  auto githyanki = RaceFactory::Create(abilities, Race::Type::Githyanki);
  ASSERT_EQ(abilities.map.find(AbilityType::Intelligence)->second.GetScore(), 1);
  ASSERT_EQ(abilities.map.find(AbilityType::Strength)->second.GetScore(), 2);
}

TEST(RaceTest, GoldDwarfCreation)
{
  Abilities abilities;
  auto dwarf = RaceFactory::Create(abilities, Race::Type::Dwarf, Dwarf::Type::GoldDwarf);
  ASSERT_EQ(abilities.map.find(AbilityType::Wisdom)->second.GetScore(), 1);
  ASSERT_EQ(abilities.map.find(AbilityType::Constitution)->second.GetScore(), 2);
}

TEST(RaceTest, ShieldDwarfCreation)
{
  Abilities abilities;
  auto dwarf = RaceFactory::Create(abilities, Race::Type::Dwarf, Dwarf::Type::ShieldDwarf);
  ASSERT_EQ(abilities.map.find(AbilityType::Strength)->second.GetScore(), 2);
  ASSERT_EQ(abilities.map.find(AbilityType::Constitution)->second.GetScore(), 2);
}

#include "character.h"

TEST(CharacterTest, HumanWarlockTheFiend)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, Race::Type::Human);
  auto the_class = ClassFactory::Create(abilities, Class::Type::Warlock, Warlock::Type::TheFiendWarlock);
  auto character = Character(abilities, std::move(race),std::move(the_class));
  ASSERT_EQ(character.GetAbility(AbilityType::Strength).value().GetScore(), 9);
  ASSERT_EQ(character.GetAbility(AbilityType::Dexterity).value().GetScore(), 13);
  ASSERT_EQ(character.GetAbility(AbilityType::Constitution).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Intelligence).value().GetScore(), 14);
  ASSERT_EQ(character.GetAbility(AbilityType::Wisdom).value().GetScore(), 11);
  ASSERT_EQ(character.GetAbility(AbilityType::Charisma).value().GetScore(), 16);
}
TEST(CharacterTest, StrongheartHalflingWizard)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, Race::Type::Halfling, Halfling::Type::StrongheartHalfling);
  auto the_class = ClassFactory::Create(abilities, Class::Type::Wizard);
  auto character = Character(abilities, std::move(race),std::move(the_class));
  ASSERT_EQ(character.GetAbility(AbilityType::Strength).value().GetScore(), 8);
  ASSERT_EQ(character.GetAbility(AbilityType::Dexterity).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Constitution).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Intelligence).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Wisdom).value().GetScore(), 10);
  ASSERT_EQ(character.GetAbility(AbilityType::Charisma).value().GetScore(), 12);
}
