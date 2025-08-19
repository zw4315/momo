#include "presentation/cli/cli_shell.h"

int main(int argc, const char* argv[]) {
  cli::CliShell cliShell;
  return cliShell.Run(argc, argv);
}
