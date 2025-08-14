
#include "boot/CompositionRoot.h"
#include "boot/Warmup.h"
#include "infrastructure/persistence/file/FileTagRepository.h"
#ifdef MOMO_HAVE_SQLITE
#include "infrastructure/persistence/sqlite/SqliteTagRepository.h"
#endif
#include <cstdlib>

namespace momo::boot {
static std::string envOr(const char* key, const char* def) {
  if (const char* v = std::getenv(key)) return std::string(v);
  return std::string(def);
}
AppContext BuildAppContext() {
  AppContext ctx{};
  auto repoChoice = envOr("MOMO_REPO", "file"); // file | sqlite
  if (repoChoice == "sqlite") {
#ifdef MOMO_HAVE_SQLITE
    auto db = envOr("MOMO_SQLITE_PATH", "tags.db");
    ctx.repo = std::make_unique<momo::infra::SqliteTagRepository>(db);
#else
    auto path = envOr("MOMO_TAGS_PATH", "tags.csv");
    ctx.repo = std::make_unique<momo::infra::FileTagRepository>(path);
#endif
  } else {
    auto path = envOr("MOMO_TAGS_PATH", "tags.csv");
    ctx.repo = std::make_unique<momo::infra::FileTagRepository>(path);
  }
  Warmup(*ctx.repo, ctx.registry);
  ctx.service = std::make_unique<momo::application::TagService>(ctx.registry, *ctx.repo, ctx.dayReg);
  return ctx;
}
} // namespace momo::boot
