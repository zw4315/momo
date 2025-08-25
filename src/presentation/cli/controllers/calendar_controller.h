#ifndef MOMO_PRESENTATION_CONTROLLERS_CALENDAR_CONTROLLER_H_
#define MOMO_PRESENTATION_CONTROLLERS_CALENDAR_CONTROLLER_H_

#include <string>

#include "app/calendar/ports/calendar_use_case.h"

namespace presentation {
namespace controllers {

class CalendarController {
 public:
  explicit CalendarController(app::calendar::ports::ICalendarUseCase& usecase)
      : usecase_(usecase) {}

  // 由上层解析后传入 YYYYMMDD
  app::calendar::dto::ViewDaysBetweenResult GetDaysBetween(const std::string& fromYmd8,
                                                 const std::string& toYmd8);

  app::calendar::dto::AddTagResult AddTag(const std::string& date_ymd8,
                                          const std::string& tag);

 private:
  app::calendar::ports::ICalendarUseCase& usecase_;
};

}  // namespace controllers
}  // namespace presentation

#endif  // MOMO_PRESENTATION_CONTROLLERS_CALENDAR_CONTROLLER_H_
