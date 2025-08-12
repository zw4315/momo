#include "service/tag_registry.h"

int TagRegistry::Index(std::string_view tag) {
  std::lock_guard<std::mutex> lock(mu_);
  auto it = name_to_idx_.find(std::string(tag));
  if (it != name_to_idx_.end()) return it->second;

  int idx = static_cast<int>(idx_to_name_.size());
  idx_to_name_.push_back(std::string(tag));
  name_to_idx_.emplace(idx_to_name_.back(), idx);
  return idx;
}

const std::string& TagRegistry::Name(int idx) const {
  std::lock_guard<std::mutex> lock(mu_);
  return idx_to_name_.at(idx);
}

int TagRegistry::Count() const {
  std::lock_guard<std::mutex> lock(mu_);
  return static_cast<int>(idx_to_name_.size());
}
