#pragma once
#include "dice.h"

class Attack
{
public:
  Attack(int num_dices, int faces): num_dices_{num_dices}, faces_{faces} {}

  Attack() = default;
  Attack& operator=(const Attack&) = default;

  virtual ~Attack(){};

  Attack(const Attack& other)
  {
    num_dices_ = other.num_dices_;
    faces_ = other.faces_;
  }

  int GetNumDices() const
  {
    return num_dices_;
  }

  int GetFaces() const
  {
    return faces_;
  }

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

class NamedAttack: public Attack
{
public:
  NamedAttack(const std::string& name, int num_dices, int faces): Attack(num_dices, faces), name_{name} {}

  NamedAttack() = default;

  NamedAttack& operator=(const NamedAttack& other)
  {
    Attack::operator=(other);
    return *this;
  }

  NamedAttack(const NamedAttack& other): Attack(other)
  {
    name_ = other.name_;
  }

  std::string GetName() const
  {
    return name_;
  }

protected:
  std::string name_;
};