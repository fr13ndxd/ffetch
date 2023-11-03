#include <iostream>

std::string terminal() {
  char *term = std::getenv("TERM_PROGRAM");
  if (term != nullptr) {
    return term;
  }
  return " ";
}
