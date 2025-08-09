#include <iostream>

#include "command_registry.h"

namespace timension::cli {

CommandRegistry& CommandRegistry::GetInstance() {
  static CommandRegistry instance;
  return instance;
}

void CommandRegistry::Register(const std::string& name, CommandHandler handler,
                               const std::string& description) {
  commands_[name] = Command{handler, description};
}

int CommandRegistry::Dispatch(int argc, const char* argv[]) const {
  if (argc < 2) {
    std::cerr << "No command provided. Use 'help'.\n";
    ShowHelp();
    return 1;
  }

  std::string cmd = argv[1];
  auto it = commands_.find(cmd);
  if (it == commands_.end()) {
    std::cerr << "Unknown command: " << cmd << "\n";
    ShowHelp();
    return 1;
  }

  std::vector<std::string> args(argv + 2, argv + argc);
  return it->second.handler(args);
}

void CommandRegistry::ShowHelp() const {
  std::cout << "Available commands:\n";
  for (const auto& [name, cmd] : commands_) {
    std::cout << "  " << name << " - " << cmd.description << "\n";
  }
}

}  // namespace timension::cli
