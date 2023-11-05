#include <fstream>
#include <sstream>
#include "./uptime.h"

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
