#ifndef TIMENSION_CLI_APP_H_
#define TIMENSION_CLI_APP_H_

#include "cli/command_registry.h"

namespace timension::cli {

class App {
 public:
  App();  // 可注入依赖（controller/service/db 等）
  int Run(int argc, const char* argv[]);

 private:
  void RegisterBuiltinCommands();  // 把“注册”从 main 搬走
  CommandRegistry registry_;
};

}  // namespace timension::cli

#endif  // TIMENSION_CLI_APP_H_
