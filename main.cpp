// main.cpp
#include <iostream>

#include "calendar_view.h"
#include "parser.h"

int main(int argc, char* argv[]) {
  CLIOptions opts = parseArguments(argc, argv);

  if (!opts.valid) {
    std::cerr << "Error: " << opts.errorMessage << "\n";
    return 1;
  }

  switch (opts.command) {
    case CommandType::View:
      printCalendarRange(opts.startYear, opts.startMonth, opts.endYear,
                         opts.endMonth);
      break;
    default:
      std::cerr << "Unsupported command.\n";
      return 1;
  }

  return 0;
}
