#pragma once
#include <random>
struct Dice
{
public:
  Dice(int faces)
  {
    std::random_device dev;
    rng_ = std::mt19937(dev());
    dist_ = std::uniform_int_distribution<std::mt19937::result_type>(1, faces);
  }
  int ThrowDice() {return dist_(rng_);}
private:
  std::mt19937 rng_;
  std::uniform_int_distribution<std::mt19937::result_type> dist_;
};
