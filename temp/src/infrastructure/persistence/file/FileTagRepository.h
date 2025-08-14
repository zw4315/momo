
#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <optional>
#include "domain/tags/ports/ITagRepository.h"

namespace momo::infra {
class FileTagRepository final : public momo::domain::ITagRepository {
public:
  explicit FileTagRepository(std::string path);
  ~FileTagRepository();
  std::vector<momo::domain::Tag> LoadAllTags() override;
  momo::domain::Tag SaveTag(const momo::domain::Tag& tag) override;
  void SaveAll(const std::vector<momo::domain::Tag>& tags) override;
private:
  std::string path_;
  int next_id_ = 1;
  void ensureFile();
  void computeNextId();
  static std::optional<std::pair<int,std::string>> parseLine(const std::string& line);
};
} // namespace momo::infra
