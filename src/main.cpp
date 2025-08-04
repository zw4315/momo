#include <iostream>

#include "Date.h"
#include "calendar_controller.h"
#include "calendar_view.h"
#include "parser.h"

int main(int argc, char* argv[]) {
  CLIOptions options;
  if (!ParseCliArgs(argc, argv, options)) {
    std::cerr << "Usage: calendar view YYYYMMDD YYYYMMDD\n";
    return 1;
  }

  if (options.command == CommandType::VIEW) {
    Date startDate = Date::FromString(options.startDateStr);
    Date endDate = Date::FromString(options.endDateStr);
    if (endDate < startDate) std::swap(startDate, endDate);

    CalendarContext ctx = BuildCalendarContext(startDate, endDate);
    PrintCalendarRange(ctx);
  } else {
    std::cerr << "Unsupported command.\n";
    return 1;
  }

  return 0;
}
