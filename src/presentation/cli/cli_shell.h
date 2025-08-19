#ifndef MOMO_CLI_APP_H_
#define MOMO_CLI_APP_H_

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "app/calendar/use_cases/calendar_service.h"
#include "infrastructure/persistence/memory/day_tags_repository_memory.h"
#include "infrastructure/time/system_clock.h"
#include "presentation/cli/commands/command_registry.h"
#include "presentation/cli/controllers/calendar_controller.h"
#include "presentation/cli/views/calendar_view.h"
namespace cli {

// 组合根：组装依赖并注册命令
class CliShell {
 public:
  CliShell();

  // 从 main 入口运行（若无参数则进入 REPL）
  int Run(int argc, const char* argv[]);

  // 运行一行，如 "view 20250501 20250512"
  cli::CmdResult RunLine(const std::string& line);

 private:
  void RegisterCommands();
  static std::vector<std::string> Tokenize(const std::string& line);

 private:
  // 依赖（从下到上）
  std::shared_ptr<infra::time::SystemClock> clock_;
  infra::persistence::memory::DayTagsRepositoryMemory repo_;
  app::calendar::usecases::CalendarService service_;
  presentation::controllers::CalendarController controller_;
  presentation::views::cli::CalendarViewCLI view_;
  cli::CommandRegistry registry_;
};

}  // namespace cli

#endif  // MOMO_CLI_APP_H_
