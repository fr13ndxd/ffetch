#include <fstream>

std::string hostname() {
  std::string hostname;
  std::ifstream hostname_file("/proc/sys/kernel/hostname");

  if (hostname_file.is_open()) {
    std::getline(hostname_file, hostname);
    return hostname;
  }

  return "not found";
}
