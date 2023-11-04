#include "./ram.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>

std::string ram() {
  std::ifstream meminfo("/proc/meminfo");
  std::string line;
  int memTotal = 0;
  int memFree = 0;
  int memBuffers = 0;
  int memCached = 0;
  int memSReclaimable = 0;
  int memAvailable = 0;

  while (std::getline(meminfo, line)) {
    std::smatch match;
    if (std::regex_search(line, match, std::regex(R"(MemTotal:\s+(\d+) kB)"))) {
      memTotal = std::stoi(match[1]);
    } else if (std::regex_search(line, match,
                                 std::regex(R"(MemFree:\s+(\d+) kB)"))) {
      memFree = std::stoi(match[1]);
    } else if (std::regex_search(line, match,
                                 std::regex(R"(Buffers:\s+(\d+) kB)"))) {
      memBuffers = std::stoi(match[1]);
    } else if (std::regex_search(line, match,
                                 std::regex(R"(Cached:\s+(\d+) kB)"))) {
      memCached = std::stoi(match[1]);
    } else if (std::regex_search(line, match,
                                 std::regex(R"(SReclaimable:\s+(\d+) kB)"))) {
      memSReclaimable = std::stoi(match[1]);
    } else if (std::regex_search(line, match,
                                 std::regex(R"(MemAvailable:\s+(\d+) kB)"))) {
      memAvailable = std::stoi(match[1]);
    }
  }

  int memUsed = memTotal - memFree - memBuffers - memCached - memSReclaimable;
  if (memAvailable > 0) {
    memUsed = memTotal - memAvailable;
  }

  double memUsedGiB = static_cast<double>(memUsed) / 1024 / 1024;
  double memTotalGiB = static_cast<double>(memTotal) / 1024 / 1024;

  std::ostringstream result;
  result << std::fixed;
  result.precision(2);
  result << memUsedGiB << " GiB / " << memTotalGiB << " GiB";
  return result.str();
}
