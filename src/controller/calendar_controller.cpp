#include <iomanip>
#include <sstream>

#include "calendar_controller.h"

static std::string FormatDate(const Date& d) {
  std::ostringstream oss;
  oss << d.year << "-" << std::setw(2) << std::setfill('0') << d.month << "-"
      << std::setw(2) << std::setfill('0') << d.day;
  return oss.str();
}

CalendarContext BuildCalendarContext(const Date& start, const Date& end) {
  CalendarContext ctx;
  ctx.startDate = start;
  ctx.endDate = end;
  ctx.today = Date::Gettoday();
  ctx.daysBetween = daysBetween(start, end);

  ctx.highlightMap[start.ToKey()] = "start";
  ctx.highlightMap[end.ToKey()] = "end";
  ctx.highlightMap[ctx.today.ToKey()] = "Gettoday";

  std::ostringstream summary;
  summary << "From " << FormatDate(start) << " to " << FormatDate(end) << ": "
          << ctx.daysBetween << " days";
  ctx.summaryMessage = summary.str();

  return ctx;
}
