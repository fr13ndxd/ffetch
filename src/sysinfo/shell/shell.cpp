#include "./shell.h"

std::string shell() {
  char *shell = std::getenv("SHELL");
  return shell ? shell : " ";
}
