// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

enum class CommandType { View, Unknown };

struct CLIOptions {
  CommandType command;
  int startYear = 0;
  int startMonth = 0;
  int endYear = 0;
  int endMonth = 0;
  bool valid = false;
  std::string errorMessage;
};

// 解析命令行参数
CLIOptions parseArguments(int argc, char* argv[]);

#endif  // PARSER_H
