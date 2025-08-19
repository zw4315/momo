#include <algorithm>
#include <cctype>
#include <string>

#include "domain/tags/rules.h"

namespace domain {
namespace tags {

static inline bool is_space_ascii(unsigned char c) {
  return std::isspace(c) != 0;
}

bool Rules::IsValid(const std::string& tag) {
  if (tag.empty() || tag.size() > kMaxLen) return false;
  for (unsigned char c : tag) {
    if (std::islower(c) || std::isdigit(c) || c == '_' || c == '-') continue;
    return false;
  }
  return true;
}

std::string Rules::Normalize(const std::string& tag) {
  // trim
  auto l = tag.begin();
  auto r = tag.end();
  while (l != r && is_space_ascii(static_cast<unsigned char>(*l))) ++l;
  while (r != l && is_space_ascii(static_cast<unsigned char>(*(r - 1)))) --r;
  std::string s(l, r);

  // tolower (ASCII)
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return s;
}

}  // namespace tags
}  // namespace domain
