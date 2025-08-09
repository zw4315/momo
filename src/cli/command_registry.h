#ifndef TIMENSION_CLI_COMMAND_REGISTRY_H_
#define TIMENSION_CLI_COMMAND_REGISTRY_H_

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace timension::cli {

using CommandHandler = std::function<int(const std::vector<std::string>& args)>;

class CommandRegistry {
 public:
  static CommandRegistry& GetInstance();

  void Register(const std::string& name, CommandHandler handler,
                const std::string& description);
  int Dispatch(int argc, const char* argv[]) const;

  void ShowHelp() const;

 private:
  struct Command {
    CommandHandler handler;
    std::string description;
  };

  std::unordered_map<std::string, Command> commands_;
};

}  // namespace timension::cli

#endif  // TIMENSION_CLI_COMMAND_REGISTRY_H_
