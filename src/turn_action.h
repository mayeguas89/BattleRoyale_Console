#pragma once

#include "dice.h"
#include "spell.h"

#include <memory>

/**
 * @brief Esta clase define los posibles movimientos que el personaje puede hacer
 * tanto fuera como dentro del combate.
 * All characters can perform at least an Action and a Bonus action per turn
 * Action is the primary resource Characters spend in order to attack or cast Spells
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
Until the start of your next turn, any
attack roll made against you has disadvantage if you
can see the attacker, and you make Dexterity saving
throws with advantage

Use an object
 */
class Character;

enum class TurnActionType
{
  Attack = 0,
  CastASpell,
  Dodge,
  UseAnObject,
  None
};

class TurnAction
{
public:
  TurnAction(Character* performer): performer_{performer} {}

  virtual void operator()() const
  {
    return;
  }

protected:
  Character* performer_;
};

class ActionToTarget: public TurnAction
{
public:
  ActionToTarget(Character* performer, Character* target): TurnAction(performer), target_{target} {}

protected:
  Character* target_;
};

class AttackToTarget: public ActionToTarget
{
public:
  AttackToTarget(Character* performer, Character* target): ActionToTarget(performer, target) {}

  void operator()() const override
  {
    if (AttackRoll())
    {
      RollDamage();
    }
  }

protected:
  /**
   * @brief To make an attack roll a d20 and add the appropriate modifiers. If the
   * total of the roll plus modifiers equals or exceeds the target’s A rmor Class (AC), the attack hits.
   * 
   */
  bool AttackRoll() const;

  void RollDamage() const;
};

class CastSpell: public ActionToTarget
{
public:
  CastSpell(Character* performer, Character* target, Spell* spell):
    ActionToTarget(performer, target),
    spell_{spell}
  {}
  void operator()() const override;

protected:
  Spell* spell_;
};

inline std::string TurnActionTypeToString(TurnActionType action)
{
  switch (action)
  {
    case TurnActionType::Attack:
      return "Attack";
    case TurnActionType::CastASpell:
      return "CastASpell";
    case TurnActionType::Dodge:
      return "Dodge";
    case TurnActionType::UseAnObject:
      return "UseAnObject";
  }
  return "None";
}
// class UseAnObject: public Action{
//   public:
//   UseAnObject(Character& performer, const Object& object): Action{performer} {}
//   virtual void operator()() {}
// }