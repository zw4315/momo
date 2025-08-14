
#include "presentation/mvc/controllers/TagsController.h"
#include <sstream>

namespace momo::presentation {
using momo::domain::time::DaysBetween;

void TagsController::Run(std::istream& in, std::ostream& out) {
  view_.ShowHelp();
  std::string line; out << "> ";
  while (std::getline(in, line)) {
    std::istringstream iss(line); std::string cmd, a, b;
    iss >> cmd >> a >> b;
    if (cmd == "add") {
      if (a.empty()) view_.ShowError("usage: add <name>");
      else view_.ShowTag(usecase_.CreateOrGet(a));
    } else if (cmd == "addtag") {
      if (a.empty()) view_.ShowError("usage: addtag <YYYY-MM-DD> [tag]");
      else { std::string tag = b.empty() ? "default" : b;
             if (usecase_.AddTagToDate(a, tag)) view_.ShowInfo("ok"); else view_.ShowInfo("already tagged"); }
    } else if (cmd == "view") {
      if (a.empty() || b.empty()) view_.ShowError("usage: view <d1> <d2>");
      else { auto days = DaysBetween(a,b); if (!days) view_.ShowError("bad date"); else view_.ShowInfo("days between: " + std::to_string(*days)); }
    } else if (cmd == "get") {
      if (a.empty()) view_.ShowError("usage: get <name>");
      else { auto id = usecase_.TryGetId(a); if (id) view_.ShowInfo("id=" + std::to_string(*id)); else view_.ShowInfo("not found"); }
    } else if (cmd == "list") {
      view_.ShowList(usecase_.ListTags());
    } else if (cmd == "help") { view_.ShowHelp();
    } else if (cmd == "quit" || cmd == "exit") { break;
    } else if (cmd.empty()) { /* ignore */ }
    else { view_.ShowError("unknown command: " + cmd); }
    out << "> ";
  }
}
} // namespace momo::presentation
