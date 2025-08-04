#include <iostream>

#include "Date.h"
#include "parser.h"

bool ParseCliArgs(int argc, char* argv[], CLIOptions& options) {
  if (argc != 2 && argc != 3) return false;

  options.command = CommandType::VIEW;
  options.startDateStr = argv[1];

  if (argc == 3) {
    options.endDateStr = argv[2];
  } else {
    options.endDateStr = Date::Gettoday().ToKey();  // 默认设为今天
  }

  return true;
}
