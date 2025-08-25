#ifndef MOMO_APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_RESULT_H_
#define MOMO_APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_RESULT_H_

#include <string>

namespace app {
namespace calendar {
namespace dto {

struct ViewDaysBetweenResult {
  std::string startDateIso;  // 8-digit dates, inclusive range boundaries: "YYYYMMDD"
  std::string endDateIso;    // 8-digit dates, inclusive range boundaries: "YYYYMMDD"
  int days;                  // 0-based days between start and end date, inclusive
};

}  // namespace dto
}  // namespace calendar
}  // namespace app

#endif  // MOMO_APP_CALENDAR_DTO_VIEW_DAYS_BETWEEN_RESULT_H_
