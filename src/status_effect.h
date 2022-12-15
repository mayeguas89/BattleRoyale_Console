#pragma once

enum class StatusEffect
{
  // An enemy is close. Creature has disadvantage on ranged attacks
  Threatened = 0,
  // Inflicts disadvantage on Strength and Dexterity saving Throws.
  Prone,
  // ...
  None
};