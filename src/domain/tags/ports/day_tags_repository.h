#ifndef MOMO_DOMAIN_TAGS_PORTS_DAY_TAGS_REPOSITORY_H_
#define MOMO_DOMAIN_TAGS_PORTS_DAY_TAGS_REPOSITORY_H_

#include <optional>

// 显式依赖领域类型（不再用前置声明）
#include "domain/calendar/date.h"
#include "domain/tags/day_tags.h"

namespace domain {
namespace tags {
namespace ports {

// 聚合仓储：以 DayTags 聚合为单位进行持久化
class IDayTagsRepository {
 public:
  virtual ~IDayTagsRepository() = default;

  // 读取某日的聚合（可能不存在）
  virtual std::optional<domain::tags::DayTags> Load(
      const domain::calendar::Date& day) = 0;

  // 保存聚合（新增或更新）。事务由调用方或实现决定。
  virtual void Save(const domain::tags::DayTags& aggregate) = 0;
};

}  // namespace ports
}  // namespace tags
}  // namespace domain

#endif  // MOMO_DOMAIN_TAGS_PORTS_DAY_TAGS_REPOSITORY_H_
