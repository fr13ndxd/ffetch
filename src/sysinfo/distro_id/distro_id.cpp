#include "distro_id.h"
#include <fstream>

std::string distro_id() {
  std::ifstream osRelease("/etc/os-release");
  std::string line, name;
  while (std::getline(osRelease, line)) {
    if (line.find("ID=") == 0) {
      name = line.substr(line.find("=") + 1);
      return name;
    }
  }
  return " ";
}
