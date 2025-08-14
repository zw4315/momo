
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <shared_mutex>
#include <algorithm>
#include "domain/tags/Tag.h"

namespace momo::domain {
class DayTagRegistry {
public:
  bool Add(const std::string& date, TagId id) {
    std::unique_lock lk(mtx_);
    auto& vec = map_[date];
    if (std::find(vec.begin(), vec.end(), id) != vec.end()) return false;
    vec.push_back(id);
    return true;
  }
  std::vector<TagId> Get(const std::string& date) const {
    std::shared_lock lk(mtx_);
    auto it = map_.find(date);
    if (it == map_.end()) return {};
    return it->second;
  }
private:
  mutable std::shared_mutex mtx_;
  std::unordered_map<std::string, std::vector<TagId>> map_;
};
} // namespace momo::domain
