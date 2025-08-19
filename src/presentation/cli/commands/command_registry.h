#ifndef MOMO_CLI_COMMAND_REGISTRY_H_
#define MOMO_CLI_COMMAND_REGISTRY_H_

#include <functional>
#include <ostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cli {

// 命令执行结果：code=0 表示成功；out/err 由上层决定如何渲染
struct CmdResult {
  int code{0};
  std::string out;
  std::string err;
};

using CmdHandler =
    std::function<CmdResult(const std::vector<std::string_view>&)>;

struct Command {
  CmdHandler handler;
  std::string description;  // 简要说明
  std::string usage;        // 用法，如 "view YYYYMMDD YYYYMMDD"
  int min_args{0};          // 最少参数
  int max_args{-1};         // -1 表示不限
};

class CommandRegistry {
 public:
  // 注册命令（包含别名）
  void Register(const std::string& name, const Command& cmd);

  // 是否存在该命令或其别名
  bool Has(std::string_view name) const;

  // 从 main(argc, argv) 分发（argv[1] 是命令名）
  CmdResult Dispatch(int argc, const char* argv[]) const;

  // 从 REPL/测试分发：argv_like[0] 是命令名
  CmdResult Dispatch(const std::vector<std::string_view>& argv_like) const;

  // 打印所有命令的帮助信息
  void ShowHelp(std::ostream& os) const;

 private:
  const Command* Find(std::string_view name) const;
  CmdResult ValidateAndRun(const Command& cmd,
                           const std::vector<std::string_view>& args) const;

 private:
  // 注意：别名也会映射到相同的 Command 拷贝（handler 相同）
  std::unordered_map<std::string, Command> map_;
};

}  // namespace cli

#endif  // MOMO_CLI_COMMAND_REGISTRY_H_
