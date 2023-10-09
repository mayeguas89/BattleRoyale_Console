#include "Windows.h"
#include "character.h"
#include "classes/factory.h"
#include "death_saving_throw.h"
#include "game_manager.h"
#include "health.h"
#include "interface.h"
#include "races/factory.h"
#include "spell_data_base.h"
#include "tournament.h"
#include "turn_action.h"
#include "weapon_data_base.h"
#include "wear_armor_data_base.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>

using namespace ::testing;
namespace fs = std::filesystem;

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
  ASSERT_EQ(ability.GetModifier(), 7);
}

TEST(CharacterTest, HumanWarlockTheFiend)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, Race::Type::Human);
  auto the_class = ClassFactory::Create(abilities, Class::Type::Warlock, Warlock::Type::TheFiendWarlock);
  auto character = Character(abilities, std::move(race), std::move(the_class));
  ASSERT_EQ(character.GetAbility(AbilityType::Strength).GetScore(), 9);
  ASSERT_EQ(character.GetAbility(AbilityType::Dexterity).GetScore(), 13);
  ASSERT_EQ(character.GetAbility(AbilityType::Constitution).GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Intelligence).GetScore(), 14);
  ASSERT_EQ(character.GetAbility(AbilityType::Wisdom).GetScore(), 11);
  ASSERT_EQ(character.GetAbility(AbilityType::Charisma).GetScore(), 16);
}

TEST(CharacterTest, StrongheartHalflingWizard)
{
  Abilities abilities;
  auto race = RaceFactory::Create(abilities, Race::Type::Halfling, Halfling::Type::StrongheartHalfling);
  auto the_class = ClassFactory::Create(abilities, Class::Type::Wizard);
  auto character = Character(abilities, std::move(race), std::move(the_class));
  ASSERT_EQ(character.GetAbility(AbilityType::Strength).GetScore(), 8);
  ASSERT_EQ(character.GetAbility(AbilityType::Dexterity).GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Constitution).GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Intelligence).GetScore(), 15);
  ASSERT_EQ(character.GetAbility(AbilityType::Wisdom).GetScore(), 10);
  ASSERT_EQ(character.GetAbility(AbilityType::Charisma).GetScore(), 12);
}

TEST(DeathSavingThrowTest, DeathSavingThrowFail)
{
  DeathSavingThrow dst;
  auto [succes, failure, heal] = dst(1);
  ASSERT_EQ(failure, 2);
  ASSERT_EQ(succes, 0);
  ASSERT_FALSE(heal);
}

TEST(DeathSavingThrowTest, DeathSavingThrowHeal)
{
  DeathSavingThrow dst;
  auto [succes, failure, heal] = dst(20);
  ASSERT_EQ(failure, 0);
  ASSERT_EQ(succes, 1);
  ASSERT_TRUE(heal);
}

TEST(DeathSavingThrowTest, DeathSavingThrowSucces)
{
  DeathSavingThrow dst;
  auto [succes, failure, heal] = dst(19);
  ASSERT_EQ(failure, 0);
  ASSERT_EQ(succes, 1);
  ASSERT_FALSE(heal);
}

TEST(DeathSavingThrowTest, DeathSavingThrowSucces2)
{
  DeathSavingThrow dst;
  dst(19);
  auto [succes, failure, heal] = dst(1);
  ASSERT_EQ(failure, 2);
  ASSERT_EQ(succes, 1);
  ASSERT_FALSE(heal);
  auto [succes1, failure1, heal1] = dst(1);
  ASSERT_EQ(failure1, 4);
  ASSERT_EQ(succes1, 1);
  ASSERT_FALSE(heal1);
}

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

  Spell spell{"Arms of Hadar", 2, 6, 1, Ability::Type::Strength, {Spell::DamageInflict::None}};
  auto attack = CastSpell{&character_one, &character_two, &spell};
  attack();
}

std::string GetFilePath(const std::string& filepath)
{
  char binary_path[MAX_PATH];
  GetModuleFileName(NULL, binary_path, MAX_PATH);
  fs::path path{binary_path};
  path = path.parent_path().make_preferred();
  path = path / filepath;
  return path.string();
}

TEST(WeaponContainerTest, MeleeWeaponTest)
{
  auto ranged_weapons = GetFilePath("cfg/final_ranged_weapons.json");
  auto melee_weapons = GetFilePath("cfg/final_melee_weapons.json");

  WeaponDataBase weapon_db;
  weapon_db.AddData({ranged_weapons, melee_weapons});

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

TEST(SpellContainerTest, SpellTest)
{
  auto final_spells = GetFilePath("cfg/final_spells.json");
  SpellDataBase spell_db;
  spell_db.AddData({final_spells});
  auto inflinct_wounds = spell_db.GetDataByName("Inflict Wounds");
  ASSERT_TRUE(inflinct_wounds);
  ASSERT_EQ(inflinct_wounds->GetFaces(), 10);
  ASSERT_EQ(inflinct_wounds->GetNumDices(), 3);
}

TEST(ArmorDataBaseTest, ArmorTest)
{
  auto final_armor = GetFilePath("cfg/final_armor.json");
  WearArmorDataBase armor_db;
  armor_db.AddData({final_armor});
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

  auto ability_modifier = character.GetAbility(handaxe->GetAttackAbilityModifier()).GetModifier();
  character.EquipWeapon(handaxe);
  character.EquipWearAmor(armor);

  ASSERT_EQ(character.GetAttackModifier(), ability_modifier);
}

struct CharacterTestDamage: Test
{
  Character character_one{CreateCharacter(Race::Type::Drow,
                                          Drow::Type::LolthSwornDrow,
                                          Class::Type::Warlock,
                                          Warlock::Type::TheFiendWarlock)};
};

TEST_F(CharacterTestDamage, ReceiveDamage)
{
  // Starting Life 8
  character_one.ReceiveDamage(10);
  ASSERT_THAT(character_one.GetState(), Character::State::Unconscious);
  character_one.ReceiveDamage(2);
  character_one.ReceiveDamage(8);
  ASSERT_THAT(character_one.GetState(), Character::State::Death);
}

struct MatchTest: Test
{
  Character character_one{CreateCharacter(Race::Type::Drow,
                                          Drow::Type::LolthSwornDrow,
                                          Class::Type::Warlock,
                                          Warlock::Type::TheFiendWarlock)};

  Character character_two{CreateCharacter(Race::Type::Halfling,
                                          Halfling::Type::StrongheartHalfling,
                                          Class::Type::Wizard,
                                          std::monostate{})};
  MatchTest()
  {
    SpellDataBase spell_db;
    spell_db.AddData(
      {"C:/Users/mayeg/Documents/U-TAD/Master/programacionAvanzada/C++/BattleRoyale/build/Debug/cfg/"
       "final_spells.json"});

    auto spells = spell_db.GetSpellsByLevel(1);
    // for (const auto& spell: spell_db.GetSpellsByLevel(1))
    // {
    //   std::cout << spell->GetName() << std::endl;
    // }

    typedef std::vector<std::shared_ptr<Spell>>::iterator Iterator;
    auto selected_spell = GameInterface::SelectFromContainer<Iterator>(spells.begin(), spells.end());

    std::cout << (*selected_spell)->GetName() << std::endl;
    // auto inflinct_wounds = spell_db.GetDataByName("Inflict Wounds");
    // auto inflinct_wounds = spell_db.GetDataByName("Inflict Wounds");
    // ASSERT_TRUE(inflinct_wounds);
    // ASSERT_EQ(inflinct_wounds->GetFaces(), 10);
    // ASSERT_EQ(inflinct_wounds->GetNumDices(), 3);
  }
};

TEST_F(MatchTest, Match)
{
  // character_one.Player player_one(std::make_unique<Character>(character_one));
  // Player player_two(std::make_unique<Character>(character_two));
  // auto match = Match(std::make_pair(player_one, player_two));
}