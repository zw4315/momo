#include <iostream>

#include "parser.h"

bool parseCLI(int argc, char* argv[], CLIOptions& out) {
  if (argc != 4 || std::string(argv[1]) != "view") {
    return false;
  }
  out.command = CommandType::VIEW;
  out.startDateStr = argv[2];
  out.endDateStr = argv[3];
  return true;
}
