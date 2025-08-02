// parser.cpp
#include <iostream>
#include <string>

#include "parser.h"

static bool parseDate(const std::string& dateStr, int& year, int& month) {
  if (dateStr.length() != 8) return false;
  try {
    year = std::stoi(dateStr.substr(0, 4));
    month = std::stoi(dateStr.substr(4, 2));
    if (month < 1 || month > 12) return false;
    return true;
  } catch (...) {
    return false;
  }
}

CLIOptions parseArguments(int argc, char* argv[]) {
  CLIOptions options;

  if (argc < 4) {
    options.errorMessage =
        "Usage: ./calendar view <start_yyyymmdd> <end_yyyymmdd>";
    return options;
  }

  std::string command = argv[1];
  if (command == "view") {
    options.command = CommandType::View;
    std::string startStr = argv[2];
    std::string endStr = argv[3];

    if (!parseDate(startStr, options.startYear, options.startMonth) ||
        !parseDate(endStr, options.endYear, options.endMonth)) {
      options.errorMessage = "Invalid date format. Use YYYYMMDD.";
      return options;
    }

    if (options.endYear < options.startYear ||
        (options.endYear == options.startYear &&
         options.endMonth < options.startMonth)) {
      options.errorMessage = "End date must not be earlier than start date.";
      return options;
    }

    options.valid = true;
  } else {
    options.errorMessage = "Unknown command: " + command;
  }

  return options;
}
