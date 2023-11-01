#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>

std::string USER() { return std::getenv("USER"); }

std::string distroName() {
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

std::string distroId() {
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

std::string wm() {
  char *wm = std::getenv("XDG_CURRENT_DESKTOP");
  if (wm != nullptr) {
    return wm;
  }
  return " ";
}

std::string shell() {
  char *sh = std::getenv("SHELL");
  if (sh != nullptr) {
    return sh;
  }
  return " ";
}

std::string terminal() {
  char *term = std::getenv("TERM_PROGRAM");
  if (term != nullptr) {
    return term;
  }
  return " ";
}

std::string ram() {
  std::ifstream meminfo("/proc/meminfo");
  std::string line;
  int memTotal = 0;
  int memFree = 0;
  int memBuffers = 0;
  int memCached = 0;
  int memSReclaimable = 0;
  int memShmem = 0;
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
                                 std::regex(R"(Shmem:\s+(\d+) kB)"))) {
      memShmem = std::stoi(match[1]);
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

std::string uptime() {
  std::ifstream uptimeFile("/proc/uptime");
  if (uptimeFile.is_open()) {
    double uptime;
    uptimeFile >> uptime;

    unsigned long seconds = static_cast<unsigned long>(uptime);
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;

    std::ostringstream formattedUptime;
    if (hours > 0) {
      formattedUptime << hours << " hours, ";
      minutes %= 60;
    }
    if (minutes > 0) {
      formattedUptime << minutes << " mins";
    }

    if (hours == 0 && minutes == 0) {
      formattedUptime << seconds << " seconds";
    }

    return formattedUptime.str();
  }

  return " ";
}
