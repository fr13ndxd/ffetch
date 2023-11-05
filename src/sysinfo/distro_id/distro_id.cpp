#include "distro_id.h"
#include <fstream>
#include <string>

std::string distro_id() {
  std::ifstream osRelease("/etc/os-release");
  std::string line, name;

  while (std::getline(osRelease, line)) {
    if (line.compare(0, 3, "ID=") == 0) {
      name = line.substr(3);
      return name;
    }
  }

  return " ";
}
