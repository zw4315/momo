#include "infrastructure/persistence/memory/day_tags_repository_memory.h"

namespace infra {
namespace persistence {
namespace memory {

using domain::calendar::Date;
using domain::tags::DayTags;

std::optional<DayTags> DayTagsRepositoryMemory::Load(const Date& day) {
  const std::string key = day.ToYmd8();
  auto it = store_.find(key);
  if (it == store_.end()) return std::nullopt;

  DayTags agg(day);
  for (const auto& t : it->second) {
    agg.AddTag(t);  // 领域内处理幂等/校验
  }
  return agg;
}

void DayTagsRepositoryMemory::Save(const DayTags& aggregate) {
  const std::string key = aggregate.date().ToYmd8();
  auto& bucket = store_[key];
  bucket.clear();
  for (const auto& t : aggregate.List()) {
    bucket.insert(t);
  }
}

}  // namespace memory
}  // namespace persistence
}  // namespace infra
