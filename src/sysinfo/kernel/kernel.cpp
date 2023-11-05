#include <fstream>
#include <regex>
#include <string>
#include "./kernel.h"

std::string kernel() {
  std::ifstream file("/proc/version");
  if (!file.is_open()) {
    return " ";
  }

  std::string kernelVersion;
  std::getline(file, kernelVersion);
  file.close();

  static const std::regex versionRegex(R"(\d+\.\d+\.\d+-\S+)");
  std::smatch match;
  if (std::regex_search(kernelVersion, match, versionRegex)) {
    return match.str();
  }

  return " ";
}
