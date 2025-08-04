#pragma once
#include <string>

enum class CommandType { VIEW };

struct CLIOptions {
  CommandType command;
  std::string startDateStr;
  std::string endDateStr;
};

bool ParseCliArgs(int argc, char* argv[], CLIOptions& options);
