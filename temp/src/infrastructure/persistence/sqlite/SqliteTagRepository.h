
#pragma once
#include <string>
#include <vector>
#include "domain/tags/ports/ITagRepository.h"
struct sqlite3;
namespace momo::infra {
class SqliteTagRepository final : public momo::domain::ITagRepository {
public:
  explicit SqliteTagRepository(const std::string& db_path);
  ~SqliteTagRepository();
  std::vector<momo::domain::Tag> LoadAllTags() override;
  momo::domain::Tag SaveTag(const momo::domain::Tag& tag) override;
  void SaveAll(const std::vector<momo::domain::Tag>& tags) override;
private:
  sqlite3* db_ = nullptr;
  void openDb(const std::string& path);
  void closeDb();
  void ensureSchema();
};
} // namespace momo::infra
