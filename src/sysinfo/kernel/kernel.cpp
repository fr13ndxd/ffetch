#include <fstream>
#include <regex>

std::string kernel() {
  std::ifstream file("/proc/version");
  if (file.is_open()) {
    std::string kernelVersion;
    std::getline(file, kernelVersion);
    file.close();
    std::regex versionRegex(R"(\d+\.\d+\.\d+-\S+)");
    std::smatch match;
    if (std::regex_search(kernelVersion, match, versionRegex)) {
      return match.str();
    }
  }
  return " ";
}
