#include "./cpu.h"
#include <fstream>
#include <regex>

std::string cpu() {
  std::ifstream cpuinfo("/proc/cpuinfo");
  std::string line;
  std::regex model_name_regex(R"(model name\s*:\s*(.*))");
  std::smatch match;

  while (std::getline(cpuinfo, line)) {
    if (std::regex_search(line, match, model_name_regex)) {
      return match[1];
    }
  }

  return " ";
}
