#include "./terminal.h"

std::string terminal() {
  char *term_program = std::getenv("TERM_PROGRAM");
  return term_program ? term_program : " ";
}
