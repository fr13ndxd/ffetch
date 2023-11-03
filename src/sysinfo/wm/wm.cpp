#include <iostream>

std::string wm() {
  char *wm = std::getenv("XDG_CURRENT_DESKTOP");
  if (wm != nullptr) {
    return wm;
  }
  return " ";
}
