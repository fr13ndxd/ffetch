#include "./distro.h"
#include <algorithm>
#include <fstream>

std::string distro() {
  std::ifstream osRelease("/etc/os-release");
  std::string line, name;
  while (std::getline(osRelease, line)) {
    if (line.find("NAME=") == 0) {
      name = line.substr(line.find("=") + 1);
      name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
      return name;
    }
  }
  return " ";
}
