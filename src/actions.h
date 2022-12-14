#pragma once

#include "character.h"
#include "dice.h"

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
class Action
{
public:
  enum class Type
  {
    Attack,
    CastASpell,
    Dodge,
    UseAnObject
  };
  Action(Character& performer): performer_{performer} {}

protected:
  Character& performer_;
};

class Attack: public Action
{
public:
  Attack(Character& performer, Character& target): Action(performer), target_{target}
  {
    if (AttackRoll()) { int damage = RollDamage(); }
  }

  /**
   * @brief To make an attack roll a d20 and add the appropriate modifiers. If the
   * total of the roll plus modifiers equals or exceeds the target’s A rmor Class (AC), the attack hits.
   * 
   */
  bool AttackRoll()
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

  int RollDamage()
  {
    int damage = performer_.RollDamage();

  }

private:
  Character& target_;
};