#pragma once
#include "dice.h"

class Attack
{
public:
  Attack(int num_dices, int faces): num_dices_{num_dices}, faces_{faces} {}
  virtual ~Attack(){};
  int GetDamage() const
  {
    int damage = 0;
    for (int i = 0; i < num_dices_; i++)
    {
      damage += SingletonDice::Get().Roll(faces_);
    }
    return damage;
  }

protected:
  int num_dices_;
  int faces_;
};