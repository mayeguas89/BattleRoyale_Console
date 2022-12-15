#pragma once

#include <string>

class Item
{
public:
  Item(const std::string& name): name_{name} {}

  Item() = default;

  Item(const Item& other): name_{other.name_} {}

  Item& operator=(const Item& other) = default;

  std::string GetName() const
  {
    return name_;
  }

protected:
  std::string name_;
};