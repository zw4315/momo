#ifndef CALENDAR_CONTROLLER_H
#define CALENDAR_CONTROLLER_H

#include <map>
#include <string>

#include "Date.h"

struct CalendarContext {
  Date startDate;
  Date endDate;
  Date today;
  int daysBetween;
  std::map<std::string, std::string> highlightMap;
  std::string summaryMessage;
};

CalendarContext buildCalendarContext(const Date& start, const Date& end);

#endif  // CALENDAR_CONTROLLER_H
