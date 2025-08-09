#include "cli/app.h"

int main(int argc, const char* argv[]) {
  timension::cli::App app;     // 可在构造里注入 controller/service
  return app.Run(argc, argv);  // 或 Run({argv, argv+argc})
}
