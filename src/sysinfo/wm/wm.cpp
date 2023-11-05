#include "./wm.h"

std::string wm() {
  char *wm = std::getenv("XDG_CURRENT_DESKTOP");
  return wm ? wm : " ";
}
