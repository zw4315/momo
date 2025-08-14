
#pragma once
#include <memory>
#include <string>
#include "domain/tags/TagRegistry.h"
#include "domain/calendar/DayTagRegistry.h"
#include "application/tags/TagService.h"
#include "application/tags/ports/ITagUseCase.h"

namespace momo::boot {
struct AppContext {
  momo::domain::TagRegistry registry;
  momo::domain::DayTagRegistry dayReg;
  std::unique_ptr<momo::domain::ITagRepository> repo;
  std::unique_ptr<momo::application::TagService> service;
  momo::application::ports::ITagUseCase& usecase() { return *service; }
};
AppContext BuildAppContext();
}
