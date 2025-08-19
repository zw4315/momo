#include <sstream>

#include "presentation/cli/commands/command_registry.h"

namespace cli {

void CommandRegistry::Register(const std::string& name, const Command& cmd) {
  map_[name] = cmd;
}

bool CommandRegistry::Has(std::string_view name) const {
  return map_.find(std::string{name}) != map_.end();
}

const Command* CommandRegistry::Find(std::string_view name) const {
  auto it = map_.find(std::string{name});
  if (it == map_.end()) return nullptr;
  return &it->second;
}

CmdResult CommandRegistry::ValidateAndRun(
    const Command& cmd, const std::vector<std::string_view>& args) const {
  const int n = static_cast<int>(args.size());
  if (n < cmd.min_args || (cmd.max_args >= 0 && n > cmd.max_args)) {
    std::ostringstream os;
    os << "usage: " << cmd.usage;
    return CmdResult{2, "", os.str()};
  }
  return cmd.handler(args);
}

CmdResult CommandRegistry::Dispatch(
    const std::vector<std::string_view>& argv_like) const {
  if (argv_like.empty()) {
    return CmdResult{2, "", "no command"};
  }
  const auto* cmd = Find(argv_like[0]);
  if (!cmd) {
    std::ostringstream os;
    os << "unknown command: " << argv_like[0];
    return CmdResult{2, "", os.str()};
  }
  std::vector<std::string_view> args;
  if (argv_like.size() > 1) {
    args.assign(argv_like.begin() + 1, argv_like.end());
  }
  return ValidateAndRun(*cmd, args);
}

CmdResult CommandRegistry::Dispatch(int argc, const char* argv[]) const {
  if (argc < 2) return CmdResult{2, "", "no command"};
  std::vector<std::string_view> argv_like;
  argv_like.reserve(static_cast<std::size_t>(argc - 1));
  for (int i = 1; i < argc; ++i) argv_like.emplace_back(argv[i]);
  return Dispatch(argv_like);
}

void CommandRegistry::ShowHelp(std::ostream& os) const {
  os << "available commands:\n";
  for (const auto& [name, cmd] : map_) {
    os << "  " << name;
    if (!cmd.description.empty()) os << "\n    " << cmd.description;
    if (!cmd.usage.empty()) os << "\n    usage: " << cmd.usage;
    os << "\n";
  }
}

}  // namespace cli
