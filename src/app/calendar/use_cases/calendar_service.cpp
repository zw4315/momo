#include <stdexcept>
#include <utility>

#include "app/calendar/use_cases/calendar_service.h"
#include "domain/calendar/date.h"
#include "domain/calendar/date_range_service.h"
#include "domain/tags/day_tags.h"

// 备注：本实现基于“方案 A（聚合仓储）”
// 要求 calendar_service.h 中的成员 repo_ 类型为
//   domain::tags::ports::IDayTagsRepository&
// 并且已包含 "domain/tags/ports/day_tags_repository.h"

namespace app {
namespace calendar {
namespace usecases {

using domain::calendar::Date;
using domain::calendar::DateRangeService;
using domain::tags::DayTags;

dto::ViewDaysBetweenResult CalendarService::ViewDaysBetween(
    const dto::ViewDaysBetweenQuery& q) {
  // 采用紧凑 8 位输入；如需兼容带横杠，可改为 Date::FromString
  const Date from = Date::FromYmd8(q.startDateIso);
  const Date to = Date::FromYmd8(q.endDateIso);

  const int days = DateRangeService::DaysBetween(from, to);
  return {q.startDateIso, q.endDateIso, days};
}

dto::AddTagResult CalendarService::AddTagToDay(const dto::AddTagCommand& cmd) {
  if (cmd.tag.empty()) {
    throw std::invalid_argument("tag must not be empty");
  }

  const Date day = Date::FromYmd8(cmd.dateIso);

  // 读取或创建聚合
  auto current = repo_.Load(day);
  // 这里的 has_value() 来自于 optional
  DayTags agg = current.has_value() ? std::move(*current) : DayTags(day);

  // 领域内处理幂等
  const bool created = agg.AddTag(cmd.tag);

  // 仅当状态变化时持久化（避免无谓写入）
  if (created) {
    repo_.Save(agg);
  }

  return {cmd.dateIso, cmd.tag, created};
}

}  // namespace usecases
}  // namespace calendar
}  // namespace app
