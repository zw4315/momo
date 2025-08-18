#ifndef MOMO_APPLICATION_CALENDAR_USECASES_CALENDAR_SERVICE_H_
#define MOMO_APPLICATION_CALENDAR_USECASES_CALENDAR_SERVICE_H_

#include "app/calendar/ports/calendar_use_case.h"
#include "domain/tags/ports/day_tags_repository.h"

namespace app {
namespace calendar {
namespace usecases {

// 应用服务（用例编排层）：
// - ViewDaysBetween：计算自然日差（要求输入为 "YYYYMMDD"；如需兼容 ISO 用
// FromString 在 .cpp 里处理）。
// - AddTagToDay：加载/创建 DayTags 聚合 -> 执行领域操作 AddTag（幂等）->
// 变更时持久化。
class CalendarService : public ports::ICalendarUseCase {
 public:
  explicit CalendarService(domain::tags::ports::IDayTagsRepository& repo)
      : repo_(repo) {}

  dto::ViewDaysBetweenResult ViewDaysBetween(
      const dto::ViewDaysBetweenQuery& q) override;

  dto::AddTagResult AddTagToDay(const dto::AddTagCommand& cmd) override;

 private:
  domain::tags::ports::IDayTagsRepository& repo_;
};

}  // namespace usecases
}  // namespace calendar
}  // namespace app

#endif  // MOMO_APPLICATION_CALENDAR_USECASES_CALENDAR_SERVICE_H_
