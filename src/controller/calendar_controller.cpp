#include <iomanip>
#include <sstream>

#include "calendar_controller.h"

static std::string formatDate(const Date& d) {
  std::ostringstream oss;
  oss << d.year << "-" << std::setw(2) << std::setfill('0') << d.month << "-"
      << std::setw(2) << std::setfill('0') << d.day;
  return oss.str();
}

CalendarContext buildCalendarContext(const Date& start, const Date& end) {
  CalendarContext ctx;
  ctx.startDate = start;
  ctx.endDate = end;
  ctx.today = Date::today();
  ctx.daysBetween = daysBetween(start, end);

  ctx.highlightMap[start.toKey()] = "start";
  ctx.highlightMap[end.toKey()] = "end";
  ctx.highlightMap[ctx.today.toKey()] = "today";

  std::ostringstream summary;
  summary << "From " << formatDate(start) << " to " << formatDate(end) << ": "
          << ctx.daysBetween << " days";
  ctx.summaryMessage = summary.str();

  return ctx;
}
