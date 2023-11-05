#include "./ram.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

std::string ram() {
  std::ifstream meminfo("/proc/meminfo");
  std::string line;
  int memTotal = 0;
  int memAvailable = 0;

  while (std::getline(meminfo, line)) {
    std::smatch match;
    if (std::regex_search(line, match, std::regex(R"(MemTotal:\s+(\d+) kB)"))) {
      memTotal = std::stoi(match[1]);
    } else if (std::regex_search(line, match, std::regex(R"(MemAvailable:\s+(\d+) kB)"))) {
      memAvailable = std::stoi(match[1]);
    }
  }

  int memUsed = memTotal - memAvailable;

  double memUsedGiB = static_cast<double>(memUsed) / 1024 / 1024;
  double memTotalGiB = static_cast<double>(memTotal) / 1024 / 1024;

  std::ostringstream result;
  result << std::fixed;
  result.precision(2);
  result << memUsedGiB << " GiB / " << memTotalGiB << " GiB";
  return result.str();
}
