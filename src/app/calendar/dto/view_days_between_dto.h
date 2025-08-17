#ifndef APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_DTO_H_
#define APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_DTO_H_

#include <string>

namespace app {
namespace calendar {
namespace dto {

struct ViewDaysBetweenQuery {
  std::string start_date_iso;
  std::string end_date_iso;
};

struct ViewDaysBetweenResult {
  int days;
};

}  // namespace dto
}  // namespace calendar
}  // namespace app

#endif  // APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_DTO_H_
