#pragma once

class Health
{
public:
  Health(int hit_die): hit_die_{hit_die}, current_life_{hit_die} {}

  void Heal(int amount)
  {
    current_life_ += amount;
  }

  // Return remaining damage
  int TakeDamage(int amount)
  {
    current_life_ = std::max(current_life_ - amount, 0);
    if (current_life_ == 0)
    {
      return std::abs(current_life_ - amount);
    }
    return 0;
  }

  int GetCurrent()
  {
    return current_life_;
  }

  int GetHitdie()
  {
    return hit_die_;
  }

private:
  int hit_die_;
  int current_life_;
};