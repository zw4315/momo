#include <iostream>
#include <sstream>

#include "cli/app.h"

namespace cli {

using presentation::controllers::CalendarController;
namespace dto = app::calendar::dto;

App::App() : repo_(), service_(repo_), controller_(service_) {
  RegisterCommands();
}

void App::RegisterCommands() {
  // view YYYYMMDD YYYYMMDD
  registry_.Register(
      "view",
      cli::Command{
          /*handler=*/[this](const std::vector<std::string_view>& args)
                          -> cli::CmdResult {
            try {
              auto res =
                  controller_.View(std::string(args[0]), std::string(args[1]));
              return cli::CmdResult{0, view_.Render(res), ""};
            } catch (const std::exception& e) {
              return cli::CmdResult{1, "", e.what()};
            }
          },
          /*description=*/"Show natural day difference between two dates.",
          /*usage=*/"view YYYYMMDD YYYYMMDD",
          /*min_args=*/2,
          /*max_args=*/2,
          /*aliases=*/{}});

  // addtag YYYYMMDD TAG
  registry_.Register(
      "addtag",
      cli::Command{/*handler=*/[this](const std::vector<std::string_view>& args)
                                   -> cli::CmdResult {
                     try {
                       auto res = controller_.AddTag(std::string(args[0]),
                                                     std::string(args[1]));
                       return cli::CmdResult{0, view_.Render(res), ""};
                     } catch (const std::exception& e) {
                       return cli::CmdResult{1, "", e.what()};
                     }
                   },
                   /*description=*/"Add a tag to a specific day (idempotent).",
                   /*usage=*/"addtag YYYYMMDD TAG",
                   /*min_args=*/2,
                   /*max_args=*/2,
                   /*aliases=*/{}});

  // help
  registry_.Register(
      "help",
      cli::Command{/*handler=*/[this](const std::vector<std::string_view>&)
                                   -> cli::CmdResult {
                     std::ostringstream os;
                     registry_.ShowHelp(os);
                     return cli::CmdResult{0, os.str(), ""};
                   },
                   /*description=*/"Show available commands.",
                   /*usage=*/"help",
                   /*min_args=*/0,
                   /*max_args=*/0,
                   /*aliases=*/{"-h", "--help", "?"}});
}

int App::Run(int argc, const char* argv[]) {
  if (argc <= 1) {
    // 简易 REPL
    std::cout << "momo CLI (type 'help' for commands, 'exit' to quit)\n";
    std::string line;
    while (true) {
      std::cout << "momo> " << std::flush;
      if (!std::getline(std::cin, line)) break;
      if (line == "exit" || line == "quit") break;
      auto r = RunLine(line);
      if (!r.out.empty()) std::cout << r.out << "\n";
      if (!r.err.empty()) std::cerr << r.err << "\n";
    }
    return 0;
  }

  // 直接从 argv 分发一次
  auto r = registry_.Dispatch(argc, argv);
  if (!r.out.empty()) std::cout << r.out << "\n";
  if (!r.err.empty()) std::cerr << r.err << "\n";
  return r.code;
}

std::vector<std::string> App::Tokenize(const std::string& line) {
  std::istringstream is(line);
  std::vector<std::string> out;
  std::string tok;
  while (is >> tok) out.push_back(tok);
  return out;
}

cli::CmdResult App::RunLine(const std::string& line) {
  auto toks = Tokenize(line);
  if (toks.empty()) return cli::CmdResult{0, "", ""};

  // tokens -> string_view（引用 toks 的存储，生命周期在本函数内有效）
  std::vector<std::string_view> views;
  views.reserve(toks.size());
  for (const auto& s : toks) views.emplace_back(s);

  return registry_.Dispatch(views);
}

}  // namespace cli
