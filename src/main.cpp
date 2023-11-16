#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sol/sol.hpp>
#include <string>
#include <map>
// other includes (systeminfo, config stuff,...)
#include "./includes.h"

std::string configDir = "/home/" + std::string(USER()) + "/.config/ffetch/";
std::string configFile = configDir + "config.lua";
sol::optional<std::string> output;

const std::string version = "0.1";
const std::string default_config = R"(
config = { 
    -- options
}
)";
const std::string help_message =
    "OPTIONS:\n"
    "   -h, --help                        Print this help and exit\n"
    "   -v, --version                     Print version and exit\n"
    "   -c, --config /path/to/config      Path to config file. Default: /home/" +
    std::string(USER()) + "/.config/ffetch/config.lua\n"
    "   --ascii-distro 'distro'           Which distro ascii art to print\n"
    "   --shell_path on/off               Display full shell path";

// options 
bool shell_path = false;

std::string replace(const std::string &str, const std::string &search,
                    const std::string &replace) {
  std::string result;
  size_t lastPos = 0;
  size_t findPos;
  while ((findPos = str.find(search, lastPos)) != std::string::npos) {
    result.append(str, lastPos, findPos - lastPos);
    result.append(replace);
    lastPos = findPos + search.length();
  }
  result.append(str, lastPos, str.length() - lastPos);
  return result;
}

std::string replaceVars(std::string str) {
  std::map<std::string, std::string> colors = {
      {"1", "\033[31m"},    // Red
      {"2", "\033[32m"},    // Green
      {"3", "\033[34m"},    // Blue
      {"4", "\033[37m"},    // White
      {"5", "\033[35m"},    // Purple
      {"6", "\033[36m"},    // Cyan
      {"7", "\033[33m"},    // Yellow
      {"8", "\033[30m"},    // Black
      {"9", "\033[91m"},    // Light Red
      {"10", "\033[92m"},   // Light Green
      {"11", "\033[94m"},   // Light Blue
      {"12", "\033[97m"},   // Light White
      {"reset", "\033[0m"}, // Reset color
      {"r", "\033[0m"}      // reset color
  };

  for (const auto &entry : colors) {
    str = replace(str, "$(color " + entry.first + ")", entry.second);
    str = replace(str, "$(c" + entry.first + ")", entry.second);
  }

  std::vector<std::pair<std::string, std::string>> vars = {
      {"$(distro)", distro()}, {"$(distroId)", distro_id()},
      {"$(kernel)", kernel()}, {"$(wm)", wm()},
      {"$(shell)", shell(shell_path)},   {"$(term)", terminal()},
      {"$(ram)", ram()},       {"$(uptime)", uptime()},
      {"$(cpu)", cpu()},       {"$(user)", USER()},
      {"$(host)", host()},     {"$(hostname)", hostname()}};

  for (const auto &entry : vars) {
    std::size_t pos = 0;
    while ((pos = str.find(entry.first, pos)) != std::string::npos) {
      str.replace(pos, entry.first.length(), entry.second);
      pos += entry.second.length();
    }
  }

  return str;
}


int main(int argc, char *argv[]) {
  if (argc != 1) {
    for (int i = 1; i < argc; i++) {
      // args
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        std::cout << help_message << std::endl;
        return 0;
      } else if (strcmp(argv[i], "-c") == 0 ||
                 strcmp(argv[i], "--config") == 0) {
        configFile = argv[i + 1];
      } else if (strcmp(argv[i], "-v") == 0 ||
                 strcmp(argv[i], "--version") == 0) {
        std::cout << version << std::endl;
        return 0;
      }
      // other
      else if (strcmp(argv[i], "--ascii-distro") == 0) {
        output = ascii(argv[i + 1]);
      }
      else if (strcmp(argv[i], "--shell_path") == 0) {
        if (i + 1 < argc) {
          const char* value = argv[i + 1];
          if (strcmp(value, "on") == 0) {
            shell_path = true;
          } else if (strcmp(value, "off") == 0) {
            shell_path = false;
          }
          } else {
            std::cerr << "USAGE:\n" << "\tffetch --shell_path on/off" << "\n\tinvalid option: " << argv[i + 1];
            return 0;
        }
      }
    }
  }

  config config(configFile);

  if (!config.ascii_distro.empty()) {
    std::string ascii_distro = config.ascii_distro;
  }
  if (config.ascii_art.has_value()) {
    output = config.ascii_art;
  }

  if (!output) {
    output = ascii();
    output = replaceVars(*output);
    std::cout << *output << std::endl;
    return 0;
  }
  if (config.ascii_art) {
    std::string output = replaceVars(*config.ascii_art);
    std::cout << output << std::endl;
    return 0;
  }

  return 0;
}
