#ifndef MOMO_PRESENTATION_VIEWS_CLI_CALENDAR_VIEW_H_
#define MOMO_PRESENTATION_VIEWS_CLI_CALENDAR_VIEW_H_

#include <string>

#include "app/calendar/ports/calendar_use_case.h"

namespace presentation {
namespace views {
namespace cli {

class CalendarViewCLI {
 public:
  std::string Render(const app::calendar::dto::ViewDaysBetweenResult& r) const;
  std::string Render(const app::calendar::dto::AddTagResult& r) const;
  std::string RenderError(const std::string& msg) const;
};

}  // namespace cli
}  // namespace views
}  // namespace presentation

#endif  // MOMO_PRESENTATION_VIEWS_CLI_CALENDAR_VIEW_H_
