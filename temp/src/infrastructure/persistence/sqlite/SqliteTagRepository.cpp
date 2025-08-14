
#include "infrastructure/persistence/sqlite/SqliteTagRepository.h"
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace momo::infra {
using momo::domain::Tag;
static void throwIf(int rc, sqlite3* db, const char* msg) {
  if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
    std::string err = msg; err += ": "; err += sqlite3_errmsg(db);
    throw std::runtime_error(err);
  }
}
SqliteTagRepository::SqliteTagRepository(const std::string& db_path) { openDb(db_path); ensureSchema(); }
SqliteTagRepository::~SqliteTagRepository() { closeDb(); }
void SqliteTagRepository::openDb(const std::string& path) {
  if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
    std::string err = sqlite3_errmsg(db_); sqlite3_close(db_); db_=nullptr;
    throw std::runtime_error("Failed to open sqlite: " + err);
  }
}
void SqliteTagRepository::closeDb() { if (db_) { sqlite3_close(db_); db_ = nullptr; } }
void SqliteTagRepository::ensureSchema() {
  const char* sql = "CREATE TABLE IF NOT EXISTS tags (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE);";
  char* errmsg = nullptr; int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errmsg);
  if (rc != SQLITE_OK) { std::string e = errmsg?errmsg:"unknown"; sqlite3_free(errmsg); throw std::runtime_error("schema error: " + e); }
}
std::vector<Tag> SqliteTagRepository::LoadAllTags() {
  std::vector<Tag> out; const char* sql = "SELECT id, name FROM tags ORDER BY id;";
  sqlite3_stmt* st = nullptr; int rc = sqlite3_prepare_v2(db_, sql, -1, &st, nullptr); throwIf(rc, db_, "prepare SELECT");
  while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
    int id = sqlite3_column_int(st, 0); const unsigned char* txt = sqlite3_column_text(st, 1);
    out.push_back(Tag{ id, reinterpret_cast<const char*>(txt ? txt : (const unsigned char*)"") });
  }
  throwIf(rc, db_, "step SELECT"); sqlite3_finalize(st); return out;
}
Tag SqliteTagRepository::SaveTag(const Tag& tag) {
  const char* sql = "INSERT INTO tags(name) VALUES (?) ON CONFLICT(name) DO NOTHING;";
  sqlite3_stmt* st = nullptr; int rc = sqlite3_prepare_v2(db_, sql, -1, &st, nullptr); throwIf(rc, db_, "prepare INSERT");
  sqlite3_bind_text(st, 1, tag.name.c_str(), -1, SQLITE_TRANSIENT); rc = sqlite3_step(st); throwIf(rc, db_, "step INSERT"); sqlite3_finalize(st);
  const char* q = "SELECT id FROM tags WHERE name=?;"; sqlite3_stmt* st2 = nullptr; rc = sqlite3_prepare_v2(db_, q, -1, &st2, nullptr); throwIf(rc, db_, "prepare SELECT id");
  sqlite3_bind_text(st2, 1, tag.name.c_str(), -1, SQLITE_TRANSIENT); rc = sqlite3_step(st2);
  if (rc != SQLITE_ROW) { sqlite3_finalize(st2); throw std::runtime_error("failed to fetch id for tag"); }
  int id = sqlite3_column_int(st2, 0); sqlite3_finalize(st2); return Tag{ id, tag.name };
}
void SqliteTagRepository::SaveAll(const std::vector<Tag>& tags) {
  char* errmsg = nullptr; int rc = sqlite3_exec(db_, "BEGIN", nullptr, nullptr, &errmsg);
  if (rc != SQLITE_OK) { std::string e = errmsg?errmsg:""; sqlite3_free(errmsg); throw std::runtime_error("BEGIN: "+e); }
  const char* sql = "INSERT INTO tags(id, name) VALUES(?, ?) ON CONFLICT(id) DO UPDATE SET name=excluded.name;";
  sqlite3_stmt* st = nullptr; rc = sqlite3_prepare_v2(db_, sql, -1, &st, nullptr); throwIf(rc, db_, "prepare UPSERT");
  for (const auto& t : tags) { sqlite3_reset(st); sqlite3_bind_int(st, 1, t.id); sqlite3_bind_text(st, 2, t.name.c_str(), -1, SQLITE_TRANSIENT); rc = sqlite3_step(st); throwIf(rc, db_, "step UPSERT"); }
  sqlite3_finalize(st); rc = sqlite3_exec(db_, "COMMIT", nullptr, nullptr, &errmsg);
  if (rc != SQLITE_OK) { std::string e = errmsg?errmsg:""; sqlite3_free(errmsg); throw std::runtime_error("COMMIT: "+e); }
}
} // namespace momo::infra
