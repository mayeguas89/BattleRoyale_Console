#pragma once

#include "character.h"
#include "dice.h"
#include "spell.h"

/**
 * @brief Esta clase define los posibles movimientos que el personaje puede hacer
 * tanto fuera como dentro del combate.
 * All characters can perform at least an Action and a Bonus action per turn
 * Action is the primary resource players spend in order to attack or cast Spells
 * Certain Skills have specific action types assigned to them. 
 * Most of these resources replenish once the turn is over
 * 
 * The most common action to take in combat is the Attack
action, whether you are swinging a sword, firing an
arrow from a bow, or brawling with your fists.
Certain features, such as the Extra Attack feature
o f the fighter, allow you to make more than one attack
with this action.
Cast a Spell
Each spell has a casting time. Most spells do have a casting time o f 1 action,
so a spellcaster often uses his or her action in combat
to cast such a spell

Dodge
Until the start o f your next turn, any
attack roll made against you has disadvantage if you
can see the attacker, and you make Dexterity saving
throws with advantage

Use an object
 */
class TurnAction
{
public:
  enum class Type
  {
    Attack,
    CastASpell,
    Dodge,
    UseAnObject
  };
  TurnAction(Character& performer): performer_{performer} {}

  virtual void operator()() const
  {
    return;
  }

protected:
  Character& performer_;
};

class ActionToTarget: public TurnAction
{
public:
  ActionToTarget(Character& performer, Character& target): TurnAction(performer), target_{target} {}

protected:
  Character& target_;
};

class AttackToTarget: public ActionToTarget
{
public:
  AttackToTarget(Character& performer, Character& target): ActionToTarget(performer, target) {}

  void operator()() const override
  {
    if (AttackRoll())
    {
      RollDamage();
    }
  }

private:
  /**
   * @brief To make an attack roll a d20 and add the appropriate modifiers. If the
   * total of the roll plus modifiers equals or exceeds the target’s A rmor Class (AC), the attack hits.
   * 
   */
  bool AttackRoll() const
  {
    // Roll A D20
    // Add modifiers
    // ability modifier:
    // melee => Strengh
    // range => Dexterity
    // character’s proficiency bonus
    // using a weapon with which you have proficiency
    // If the d20 roll for an attack is a 20, the attack hits regardless o f any modifiers or the target’s AC
    // If the d20 roll for an attack is a 1, the attack m isses regardless of any modifiers or the target’s AC.
    int attack_roll = SingletonDice::Get().Roll(20);
    if (attack_roll == 1)
      return false;
    if (attack_roll == 20)
      return true;

    attack_roll += performer_.GetAttackModifier();

    // TODO: ADD PROEFICIENCY BONUS OF ATTACKER

    auto defender_ac = target_.GetArmorClass();

    return attack_roll > defender_ac ? true : false;
  }

  void RollDamage() const
  {
    target_.ReceiveDamage(performer_.RollDamage());
  }
};

class CastSpell: public ActionToTarget
{
public:
  CastSpell(Character& performer, Character& target, const Spell& spell):
    ActionToTarget(performer, target),
    spell_{spell}
  {}
  void operator()() const override
  {
    auto dc = performer_.GetDifficultyClass();
    auto st = target_.SavingThrows(spell_.GetAbilityTypeSavingThrows());
    if ( dc > st)
    {
      target_.ReceiveDamage(spell_.GetDamage());
      // target_.SetStatusEffect(spell_.GetStatusEffect());
    }
    else target_.ReceiveDamage(spell_.GetDamage()/2);
  }

private:
  Spell spell_;
};

// class UseAnObject: public Action{
//   public:
//   UseAnObject(Character& performer, const Object& object): Action{performer} {}
//   virtual void operator()() {}
// }