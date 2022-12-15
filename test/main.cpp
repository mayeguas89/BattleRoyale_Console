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

#include "races/factory.h"
#include "races/race.h"

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
#include "classes/factory.h"

TEST(CharacterTest, HumanWarlockTheFiend)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, Race::Type::Human);
  auto the_class = ClassFactory::Create(abilities, Class::Type::Warlock, Warlock::Type::TheFiendWarlock);
  auto character = Character(abilities, std::move(race), std::move(the_class));
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
  auto character = Character(abilities, std::move(race), std::move(the_class));
  ASSERT_EQ(character.GetAbility(AbilityType::Strength).value().GetScore(), 8);
  ASSERT_EQ(character.GetAbility(AbilityType::Dexterity).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Constitution).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Intelligence).value().GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Wisdom).value().GetScore(), 10);
  ASSERT_EQ(character.GetAbility(AbilityType::Charisma).value().GetScore(), 12);
}

#include "health.h"

struct HealthTest: Test
{
  int hit_points = 12;
  Health h{hit_points};
};

TEST_F(HealthTest, HitPoints)
{
  ASSERT_EQ(h.GetHitPoints(), 12);
}

TEST_F(HealthTest, TakeDamageReturnsZeroIfDamageIsLessThanCurrentLife)
{
  ASSERT_EQ(h.TakeDamage(1), 0);
}

TEST_F(HealthTest, TakeDamageReturnsZeroIfDamageIsEqualToCurrentLife)
{
  ASSERT_EQ(h.TakeDamage(12), 0);
}

TEST_F(HealthTest, TakeDamageReturnsRemainingIfDamageIsGreaterThanCurrentLife)
{
  ASSERT_EQ(h.TakeDamage(13), 1);
}

TEST_F(HealthTest, Heal)
{
  auto last_life = h.GetCurrent();
  h.Heal(2);
  ASSERT_EQ(h.GetCurrent(), last_life + 2);
}

#include "turn_action.h"

Character CreateCharacter(Race::Type race_type, Subrace subrace, Class::Type class_type, Subclass subclass)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, race_type, subrace);
  auto the_class = ClassFactory::Create(abilities, class_type, subclass);
  Character character(abilities, std::move(race), std::move(the_class));
  return character;
}

TEST(ActionTest, CastSpell)
{
  auto character_one = CreateCharacter(Race::Type::Drow,
                                       Drow::Type::LolthSwornDrow,
                                       Class::Type::Warlock,
                                       Warlock::Type::TheFiendWarlock);
  auto character_two = CreateCharacter(Race::Type::Halfling,
                                       Halfling::Type::StrongheartHalfling,
                                       Class::Type::Wizard,
                                       std::monostate{});

  Spell spell{"Arms of Hadar", 2, 6, 1, Ability::Type::Strength};
  auto attack = CastSpell{character_one, character_two, spell};
  attack();
}

#include "weapon_data_base.h"

#include <fstream>

TEST(WeaponContainerTest, MeleeWeaponTest)
{
  WeaponDataBase weapon_db;
  weapon_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                     "simpleRangedWeapons.json",
                     "C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                     "simpleMeleeWeapons.json"});
  auto barbed_dagger = weapon_db.GetDataByName("Barbed Dagger");

  ASSERT_TRUE(barbed_dagger);
  ASSERT_EQ(barbed_dagger->GetFaces(), 4);
  ASSERT_EQ(barbed_dagger->GetNumDices(), 2);
  ASSERT_EQ(barbed_dagger->GetAttackAbilityModifier(), Ability::Type::Strength);

  auto dart = weapon_db.GetDataByName("Dart");
  ASSERT_TRUE(dart);
  ASSERT_EQ(dart->GetFaces(), 4);
  ASSERT_EQ(dart->GetNumDices(), 1);
  ASSERT_EQ(dart->GetAttackAbilityModifier(), Ability::Type::Dexterity);
}

#include "spell_data_base.h"

TEST(SpellContainerTest, SpellTest)
{
  SpellDataBase spell_db;
  spell_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                    "final_spells.json"});
  auto inflinct_wounds = spell_db.GetDataByName("Inflict Wounds");
  ASSERT_TRUE(inflinct_wounds);
  ASSERT_EQ(inflinct_wounds->GetFaces(), 10);
  ASSERT_EQ(inflinct_wounds->GetNumDices(), 3);
}

#include "wear_armor_data_base.h"

TEST(ArmorDataBaseTest, ArmorTest)
{
  WearArmorDataBase armor_db;
  armor_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                    "final_armor.json"});
  auto leather_armor = armor_db.GetDataByName("Leather Armor");
  auto breastplate = armor_db.GetDataByName("Breastplate");
  auto chain_mail = armor_db.GetDataByName("Chain Mail");
  ASSERT_TRUE(chain_mail);
  ASSERT_EQ(leather_armor->GetWearArmorClass(5), leather_armor->GetArmorClass() + 5);
  ASSERT_EQ(breastplate->GetWearArmorClass(5), breastplate->GetArmorClass() + 2);
  ASSERT_EQ(breastplate->GetWearArmorClass(1), breastplate->GetArmorClass() + 1);
  ASSERT_EQ(chain_mail->GetWearArmorClass(5), chain_mail->GetArmorClass());
}

TEST(CharacterAssignWeaponAndArmors, Simple)
{
  auto character =
    CreateCharacter(Race::Type::Dwarf, Dwarf::Type::ShieldDwarf, Class::Type::Wizard, std::monostate{});
  WeaponDataBase weapon_db;
  weapon_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                     "simpleRangedWeapons.json",
                     "C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                     "simpleMeleeWeapons.json"});
  WearArmorDataBase armor_db;
  armor_db.AddData({"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
                    "final_armor.json"});

  ASSERT_EQ(character.GetAttackModifier(), 0);

  auto handaxe = weapon_db.GetDataByName("Handaxe");
  ASSERT_TRUE(handaxe);
  auto armor = armor_db.GetDataByName("Studded Leather Armor");
  ASSERT_TRUE(armor);

  auto ability_modifier = character.GetAbility(handaxe->GetAttackAbilityModifier())->GetModifier();
  character.EquipWeapon(handaxe);
  character.EquipWearAmor(armor);

  ASSERT_EQ(character.GetAttackModifier(), ability_modifier);
  // Va con el dado por lo que no se puede saber
  // ASSERT_EQ(character.RollDamage(), character.GetAttackModifier() + ability_modifier);
}