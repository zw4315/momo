
#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include "application/tags/ports/ITagUseCase.h"
#include "presentation/mvc/views/TagView.h"
#include "domain/time/Date.h"

namespace momo::presentation {
class TagsController {
public:
  TagsController(momo::application::ports::ITagUseCase& usecase, TagView& view)
    : usecase_(usecase), view_(view) {}
  void Run(std::istream& in, std::ostream& out);
private:
  momo::application::ports::ITagUseCase& usecase_;
  TagView& view_;
};
} // namespace momo::presentation
