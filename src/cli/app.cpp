#include <iostream>

#include "cli/app.h"
#include "controller/controller.h"
#include "utils/date_utils.h"

using timension::cli::CommandRegistry;

namespace timension::cli {

App::App() { RegisterBuiltinCommands(); }

void App::RegisterBuiltinCommands() {
  auto& r = registry_;

  r.Register(
      "help",
      [this](auto) {
        r.ShowHelp();
        return 0;
      },
      "Show help message");

  r.Register(
      "add",
      [](const auto& args) {
        if (args.empty()) {
          std::cerr << "Usage: add <event-text>\n";
          return 1;
        }
        std::string text;
        for (auto& w : args) {
          if (!text.empty()) text += " ";
          text += w;
        }
        return controller::AddEvent(text);
      },
      "Add an event");

  r.Register(
      "view",
      [](const auto& args) {
        using namespace timension::utils;
        if (args.empty())
          return controller::ViewAllEvents();
        else if (args.size() == 1)
          return controller::ViewEvents(GetTodayDateStr(), args[0]);
        else if (args.size() == 2)
          return controller::ViewEvents(args[0], args[1]);
        std::cerr << "Usage: view [end] | view <start> <end>\n";
        return 1;
      },
      "View events");
}

int App::Run(int argc, const char* argv[]) {
  return registry_.Dispatch(argc, argv);
}

}  // namespace timension::cli
