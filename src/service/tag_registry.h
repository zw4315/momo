#ifndef SERVICE_TAG_REGISTRY_H_
#define SERVICE_TAG_REGISTRY_H_

#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// 运行时标签注册中心：字符串 tag → 位索引
class TagRegistry {
 public:
  // 获取已存在索引；不存在则分配新索引（线程安全）
  int Index(std::string_view tag);

  // 根据索引获取标签名
  const std::string& Name(int idx) const;

  // 获取已注册标签数量
  int Count() const;

 private:
  mutable std::mutex mu_;
  std::unordered_map<std::string, int> name_to_idx_;
  std::vector<std::string> idx_to_name_;
};

#endif  // SERVICE_TAG_REGISTRY_H_
