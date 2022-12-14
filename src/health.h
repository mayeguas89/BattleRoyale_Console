#pragma once

class Health
{
public:
  Health(int hit_points): hit_points_{hit_points}, current_life_{hit_points} {}
  Health() = default;
  void Heal(int amount)
  {
    current_life_ += amount;
  }

  // Return remaining damage
  int TakeDamage(int amount)
  {
    auto old_life = current_life_;
    current_life_ = std::max(current_life_ - amount, 0);
    if (current_life_ == 0)
    {
      return std::abs(old_life - amount);
    }
    return 0;
  }

  int GetCurrent()
  {
    return current_life_;
  }

  int GetHitPoints()
  {
    return hit_points_;
  }

private:
  int hit_points_;
  int current_life_;
};