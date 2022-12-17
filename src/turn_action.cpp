#include "turn_action.h"

#include "character.h"

void CastSpell::operator()() const
{
  fmt::print("\n** Casting = {} **\n", spell_->GetName());\

  auto dc = performer_->GetDifficultyClass();
  auto st = target_->SavingThrows(spell_->GetAbilityTypeSavingThrows());
  
  fmt::print("\n** DefenseClass={}; SavingThrows={} **\n", dc, st);
  
  if (dc > st)
  {
    target_->ReceiveDamage(spell_->GetDamage());
    // target_->SetStatusEffect(spell_->GetStatusEffect());
  }
  else
    target_->ReceiveDamage(spell_->GetDamage() / 2);
  
}

void AttackToTarget::RollDamage() const
{
  auto damage = performer_->RollDamage();

  fmt::print("\n** RollDamage={} **\n", damage);

  target_->ReceiveDamage(damage);
}

bool AttackToTarget::AttackRoll() const
{
  // Roll A D20
  // Add modifiers
  // ability modifier:
  // melee => Strengh
  // range => Dexterity
  // Character’s proficiency bonus
  // using a weapon with which you have proficiency
  // If the d20 roll for an attack is a 20, the attack hits regardless of any modifiers or the target’s AC
  // If the d20 roll for an attack is a 1, the attack m isses regardless of any modifiers or the target’s AC.
  int attack_roll = SingletonDice::Get().Roll(20);
  if (attack_roll == 1)
    return false;
  if (attack_roll == 20)
    return true;

  attack_roll += performer_->GetAttackModifier();

  // TODO: ADD PROEFICIENCY BONUS OF ATTACKER

  auto defender_ac = target_->GetArmorClass();

  fmt::print("\n** AttackRoll={}; DefenderAc={} **\n", attack_roll, defender_ac);

  return attack_roll > defender_ac ? true : false;
}
