#include "character.h"

#include "game_manager.h"
#include "turn_action.h"

#include <tabulate/table.hpp>

#include <algorithm>
#include <iostream>

Ability Character::GetAbility(Ability::Type type) const
{
  return abilities_.GetAbility(type);
}

void Character::EquipShield(std::shared_ptr<Shield> shield)
{
  if (!shield_)
  {
    shield_ = shield;
    return;
  }
  int previous_ac =
    helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity).GetModifier(), wear_armor_, shield_);
  int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity).GetModifier(), wear_armor_, shield);
  if (new_ac > previous_ac)
    shield_ = shield;
}

void Character::EquipWeapon(std::shared_ptr<Weapon> weapon)
{
  if (!weapon_)
  {
    weapon_ = weapon;
    return;
  }
  if (weapon->GetDamage() > weapon_->GetDamage())
    weapon_ = weapon;
}

void Character::ReceiveDamage(int damage)
{
  // fmt::print("\n** ReceiveDamage={} **\n", damage);

  int remaning_damage = health_.TakeDamage(damage);

  int current_life = health_.GetCurrent();

  if (current_life == 0)
  {
    if (remaning_damage >= health_.GetHitPoints())
    {
      state_ = State::Death;
    }
    else
    {
      if (state_ == State::Unconscious)
        death_saving_throw_.AddFailure();
      else
        state_ = State::Unconscious;
    }
  }
}

TurnActionType Character::DoAction()
{
  if (state_ == State::Unconscious)
  {
    auto [succes, failure, heal] = death_saving_throw_();

    if (heal || succes >= 3)
    {
      health_.Heal(1);
      state_ = State::Stable;
      death_saving_throw_.Restart();
    }

    if (failure >= 3)
    {
      state_ = State::Death;
    }

    if (CanThrowSpels())
    {
      if (GetHealingSpell())
        TurnActionType::CastASpell;
    }

    return TurnActionType::None;
  }

  if (state_ == State::Death)
    return TurnActionType::None;

  if (spells_.size() > 0)
  {
    return TurnActionType::CastASpell;
  }

  return TurnActionType::Attack;
}

void Character::LevelUp()
{
  level_++;

  fmt::print("\n ** Leveling up ** \n");
  auto amount = class_->GetHitPointsPerLevel() + GetAbilityModifier(AbilityType::Constitution);

  fmt::print("\n ** Incrementa {} hit points a los hit points actuales ** \n", amount);

  health_.AddHitPoints(amount);

  for (const auto& ability: class_->GetPrimaryHabilities())
  {
    fmt::print("\n ** Incrementa la habilidad {} ** \n", AbilityTypeToString(ability));
    abilities_.AddToAbility(ability, 1);
  }

  if (CanThrowSpels())
  {
    spell_slots_++;
    auto spells_db = GameManager::Get().GetSpellDB();
    auto spells = spells_db.GetSpellsByLevel(level_);
    auto spell = spells.at(SingletonDice::Get().Roll(static_cast<int>(spells.size())) - 1);

    fmt::print("\n ** Ahora puede usar el hechizo {} ** \n", spell->GetName());

    spells_.push_back(spell);
  }
}

void Character::PrintAbilities()
{
  tabulate::Table sub_table;
  sub_table.add_row({"Abilities"});
  sub_table.add_row({abilities_.GetAbilitiesTable()});
  std::cout << sub_table << std::endl;
}

void Character::SetStatsTable(tabulate::Table& stats_table)
{
  stats_table[1][0].set_text({fmt::format("{}", health_.GetCurrent())});
  stats_table[1][0].format().font_background_color(tabulate::Color::green).font_style({tabulate::FontStyle::bold});
  if (health_.GetCurrent() < health_.GetHitPoints() / 2)
    stats_table[1][0].format().font_background_color(tabulate::Color::red).font_style({tabulate::FontStyle::bold});

  stats_table[1][1].set_text({StateToString(state_)});
  stats_table[1][1].format().font_background_color(tabulate::Color::green).font_style({tabulate::FontStyle::bold});
  if (state_ == State::Death)
    stats_table[1][1].format().font_background_color(tabulate::Color::red).font_style({tabulate::FontStyle::bold});
}

void Character::EquipWearAmor(std::shared_ptr<WearArmor> wear_armor)
{
  if (!wear_armor_)
  {
    wear_armor_ = wear_armor;
    return;
  }
  auto dexterity_modifier = GetAbilityModifier(Ability::Type::Dexterity);

  auto previous_ac = helpers::GetArmorClass(dexterity_modifier, wear_armor_, shield_);
  auto new_ac = helpers::GetArmorClass(dexterity_modifier, wear_armor, shield_);
  if (new_ac > previous_ac)
    wear_armor_ = wear_armor;
}