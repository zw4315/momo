#ifndef MOMO_DOMAIN_TAGS_RULES_H_
#define MOMO_DOMAIN_TAGS_RULES_H_

#include <string>

namespace domain {
namespace tags {

// 标签命名规则：
// - 允许字符：a-z 0-9 _ -
// - 最长 32 字符
// - 规范化：去首尾空白 + 转小写（ASCII）
struct Rules {
  static constexpr std::size_t kMaxLen = 32;

  // 只做校验；不改变输入
  static bool IsValid(const std::string& tag);

  // 规范化：trim + tolower（ASCII）
  static std::string Normalize(const std::string& tag);
};

}  // namespace tags
}  // namespace domain

#endif  // MOMO_DOMAIN_TAGS_RULES_H_
