#pragma once

#include <memory>
#include <vector>

template<typename T>
class DataBase
{
public:
  virtual ~DataBase() = default;
  virtual std::vector<std::shared_ptr<T>> GetData() = 0;
  virtual std::shared_ptr<T> GetDataByName(const std::string& name) = 0;
  virtual void AddData(const std::vector<std::string>& filenames) = 0;
};
