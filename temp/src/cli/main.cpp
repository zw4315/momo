
#include <iostream>
#include "boot/CompositionRoot.h"
#include "presentation/mvc/views/TagView.h"
#include "presentation/mvc/controllers/TagsController.h"

int main() {
  auto app = momo::boot::BuildAppContext();
  momo::presentation::TagView view(std::cout);
  momo::presentation::TagsController controller(app.usecase(), view);
  controller.Run(std::cin, std::cout);
  return 0;
}
