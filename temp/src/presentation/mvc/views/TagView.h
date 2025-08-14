
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "domain/tags/Tag.h"

namespace momo::presentation {
class TagView {
public:
  explicit TagView(std::ostream& os) : os_(os) {}
  void ShowTag(const momo::domain::Tag& t) { os_ << "Tag -> id=" << t.id << ", name=" << t.name << "\n"; }
  void ShowList(const std::vector<momo::domain::Tag>& ts) {
    os_ << "All Tags (" << ts.size() << "):\n"; for (const auto& t : ts) ShowTag(t);
  }
  void ShowHelp() {
    os_ << "Commands:\n"
           "  add <name>           - create or get a tag\n"
           "  addtag <date> [tag]  - tag a day (YYYY-MM-DD), default tag 'default'\n"
           "  view <d1> <d2>       - days between (YYYY-MM-DD)\n"
           "  get <name>           - id by name\n"
           "  list                 - list tags\n"
           "  help                 - this help\n"
           "  quit/exit            - leave\n";
  }
  void ShowInfo(const std::string& s) { os_ << s << "\n"; }
  void ShowError(const std::string& e) { os_ << "[error] " << e << "\n"; }
private:
  std::ostream& os_;
};
} // namespace momo::presentation
