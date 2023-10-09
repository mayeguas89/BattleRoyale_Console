#pragma once

#include "dice.h"

#include <utility>

/**
 * @brief Clase que gestiona el SavingThrow de la muerte
 */
class DeathSavingThrow
{
public:
  struct Result
  {
    Result(int p_success, int p_failure, bool p_heal):
      success_count{p_success},
      failure_count{p_failure},
      heal{p_heal}
    {}
    int success_count;
    int failure_count;
    bool heal;
  };
  DeathSavingThrow() {}

  Result operator()(int roll = -1)
  {
    // On your third success, you become stable (see
    // below). On your third failure, you die
    if (roll == -1)
      roll = SingletonDice::Get().Roll(20);

    if (roll == 1)
      failure_counter_ += 2;
    else
    {
      if (roll > 10)
        success_counter_++;
      else
        failure_counter_++;
    }

    return Result{success_counter_, failure_counter_, roll == 20};
  }

  void AddFailure()
  {
    failure_counter_++;
  }

  void Restart()
  {
    failure_counter_ = 0;
    success_counter_ = 0;
  }

private:
  int failure_counter_{0};
  int success_counter_{0};
};