
#pragma once
#include "domain/tags/TagRegistry.h"
#include "domain/tags/ports/ITagRepository.h"
namespace momo::boot {
inline void Warmup(momo::domain::ITagRepository& repo, momo::domain::TagRegistry& reg) {
  reg.LoadFromSnapshot(repo.LoadAllTags());
}
}
