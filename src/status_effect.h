#pragma once

enum class StatusEffect
{
  // Creature has disadvantage on ranged attacks
  Threatened = 0,
  // Inflicts disadvantage on Strength and Dexterity saving Throws.
  Prone,
  // Slashing causes bleeding
  Bleeding,
  // disadvantage on attack rolls and ability checks.
  Poisoned,
  // 1d4 per tourn
  Fired,
  // disadvantage on AttackRoll
  Frightened,
  // Disadvantage on Wisdom Saving Throws loses dexterity in ability checks
  Dazed,
  // 1d4 per tourn
  Pinched,
  //  cant move
  Stunned,
  // ...
  None
};