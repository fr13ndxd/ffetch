#include <iostream>

std::string shell() {
  char *sh = std::getenv("SHELL");
  if (sh != nullptr) {
    return sh;
  }
  return " ";
}
