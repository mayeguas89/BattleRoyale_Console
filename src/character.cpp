#include "character.h"

#include "turn_action.h"

#include <tabulate/table.hpp>

#include <iostream>

std::optional<Ability> Character::GetAbility(Ability::Type type)
{
  if (auto it = abilities_.map.find(type); it != abilities_.map.end())
  {
    return it->second;
  }
  return std::nullopt;
}

void Character::EquipShield(std::shared_ptr<Shield> shield)
{
  if (!shield_)
  {
    shield_ = shield;
    return;
  }
  int previous_ac =
    helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield_);
  int new_ac = helpers::GetArmorClass(GetAbility(Ability::Type::Dexterity)->GetModifier(), wear_armor_, shield);
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
  fmt::print("\n** ReceiveDamage={} **\n", damage);

  int remaning_damage = health_.TakeDamage(damage);

  int current_life = health_.GetCurrent();

  if (current_life == 0)
  {
    if (remaning_damage == health_.GetHitPoints())
    {
      state_ = State::Death;
    }
    else
    {
      // This unconsciousness ends if you regain any hit points
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

    tabulate::Table dst_table;
    dst_table.add_row({"Succes", "Failure", "Heal"});
    dst_table.add_row({fmt::format("{}", succes), fmt::format("{}", failure), fmt::format("{}", heal)});
    dst_table[1][0].format().font_background_color(tabulate::Color::blue).font_style({tabulate::FontStyle::bold});
    dst_table[1][1].format().font_background_color(tabulate::Color::red).font_style({tabulate::FontStyle::bold});
    dst_table[1][2].format().font_background_color(tabulate::Color::green).font_style({tabulate::FontStyle::bold});
    std::cout << dst_table << std::endl;

    if (heal)
      health_.Heal(1);
    if (succes >= 3)
    {
      state_ = State::Stable;
      death_saving_throw_.Restart();
    }
    else if (failure == 3)
    {
      state_ = State::Death;
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

void Character::PrintStats()
{
  tabulate::Table stats_table;
  stats_table.add_row({"Current Health", "State"});
  stats_table.add_row({fmt::format("{}", health_.GetCurrent()), StateToString(state_)});
  if (health_.GetCurrent() > health_.GetHitPoints() / 2)
  {
    stats_table[1][0]
      .format()
      .font_background_color(tabulate::Color::green)
      .font_style({tabulate::FontStyle::bold});
  }
  else
  {
    stats_table[1][0].format().font_background_color(tabulate::Color::red).font_style({tabulate::FontStyle::bold});
  }
  std::cout << "\n" << stats_table << "\n";
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