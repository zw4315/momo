#include "presentation/cli/controllers/calendar_controller.h"

namespace presentation {
namespace controllers {

namespace dto = app::calendar::dto;

dto::ViewDaysBetweenResult CalendarController::View(const std::string& fromYmd8,
                                                    const std::string& toYmd8) {
  dto::ViewDaysBetweenQuery q{fromYmd8, toYmd8};
  return usecase_.ViewDaysBetween(q);
}

dto::AddTagResult CalendarController::AddTag(const std::string& date_ymd8,
                                             const std::string& tag) {
  dto::AddTagCommand cmd{date_ymd8, tag};
  return usecase_.AddTagToDay(cmd);
}

}  // namespace controllers
}  // namespace presentation
