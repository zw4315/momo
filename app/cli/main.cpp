#include "cli/app.h"

int main(int argc, const char* argv[]) {
  cli::App app;
  return app.Run(argc, argv);
}
