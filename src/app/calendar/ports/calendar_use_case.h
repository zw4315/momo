#ifndef MOMO_APPLICATION_CALENDAR_PORTS_CALENDAR_USE_CASE_H_
#define MOMO_APPLICATION_CALENDAR_PORTS_CALENDAR_USE_CASE_H_

#include "app/calendar/dto/add_tag_command.h"
#include "app/calendar/dto/add_tag_result.h"
#include "app/calendar/dto/view_days_between_query.h"
#include "app/calendar/dto/view_days_between_result.h"

namespace app {
namespace calendar {
namespace ports {

class ICalendarUseCase {
 public:
  virtual ~ICalendarUseCase() = default;

  // 功能1：计算日期差（自然日差；同日=0；from>to 由实现抛异常）
  virtual dto::ViewDaysBetweenResult ViewDaysBetween(
      const dto::ViewDaysBetweenQuery& q) = 0;

  // 功能2：为指定日期添加标签（幂等；返回 created 标识）
  virtual dto::AddTagResult AddTagToDay(const dto::AddTagCommand& cmd) = 0;
};

}  // namespace ports
}  // namespace calendar
}  // namespace app

#endif  // MOMO_APPLICATION_CALENDAR_PORTS_CALENDAR_USE_CASE_H_
