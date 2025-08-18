#ifndef MOMO_INFRASTRUCTURE_PERSISTENCE_MEMORY_DAY_TAGS_REPOSITORY_MEMORY_H_
#define MOMO_INFRASTRUCTURE_PERSISTENCE_MEMORY_DAY_TAGS_REPOSITORY_MEMORY_H_

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "domain/calendar/date.h"
#include "domain/tags/day_tags.h"
#include "domain/tags/ports/day_tags_repository.h"

namespace infra {
namespace persistence {
namespace memory {

// 纯内存版聚合仓储：适合 V1 跑通与单测
class DayTagsRepositoryMemory : public domain::tags::ports::IDayTagsRepository {
 public:
  ~DayTagsRepositoryMemory() override = default;

  std::optional<domain::tags::DayTags> Load(
      const domain::calendar::Date& day) override;

  void Save(const domain::tags::DayTags& aggregate) override;

  // 仅供测试：查看内部存储
  const std::unordered_map<std::string, std::unordered_set<std::string>>& raw()
      const {
    return store_;
  }

 private:
  // key = "YYYYMMDD"
  std::unordered_map<std::string, std::unordered_set<std::string>> store_;
};

}  // namespace memory
}  // namespace persistence
}  // namespace infra

#endif  // MOMO_INFRASTRUCTURE_PERSISTENCE_MEMORY_DAY_TAGS_REPOSITORY_MEMORY_H_
