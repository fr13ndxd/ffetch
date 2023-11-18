#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sol/sol.hpp>
#include <string>
#include <map>
#include <getopt.h>
// other includes (systeminfo, config stuff,...)
#include "./includes.h"

const std::string HOME = std::getenv("HOME");
std::string configFile = HOME + "/.config/ffetch/config.lua";
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
    "   --ascii-always-small on/off       Always display small ascii art version"
    "   --shell-path on/off               Display full shell path";

// options 
bool shell_path = false;
bool ascii_always_small = false;

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
    auto replaceColors = [&entry](std::string &str, const std::string &target) {
      std::size_t pos = 0;
      while((pos = str.find(target, pos)) != std::string::npos) {
        str.replace(pos, target.length(), entry.second);
        pos += entry.second.length();
      }
    };
    replaceColors(str, "$(c" + entry.first + ")");
    replaceColors(str, "$(color " + entry.first + ")");
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
  int option;
  // options
  std::string ascii_distro;
  config config(configFile);

  if(!config.ascii_distro.empty()) ascii_distro = config.ascii_distro;
  if(config.ascii_art.has_value()) output = replaceVars(*config.ascii_art);
  if(config.shell_path) shell_path = config.shell_path;

  static struct option args[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 'v'},
      {"config", required_argument, 0, 'c'},
      {"ascii-distro", required_argument, 0, 'a'},
      {"ascii-always-small", no_argument, 0, 'l'},
      {"shell-path", required_argument, 0, 's'},
      {0, 0, 0, 0}
  };

  while ((option = getopt_long(argc, argv, "hvc:", args, nullptr)) != -1) {
    switch (option) {
      case 'h':
        std::cout << help_message << std::endl;
        return 0;
      case 'v':
        std::cout << version << std::endl;
        return 0;
      case 'c':
        configFile = optarg;
        break;
      case 'a':
        ascii_distro = optarg;
        break;
      case 's':
        shell_path = (strcmp(optarg, "on") == 0);
        break;
      case 'l':
        ascii_always_small = true;
        break;
      default:
        return 1;
    }
  }

  if (!output.has_value()) {
   // output = ascii_distro.empty() ? ascii() : ascii(ascii_distro);
    output = ascii(ascii_distro, ascii_always_small);
    output = replaceVars(*output);
    std::cout << *output << std::endl;
    return 0;
  } else {
    std::cout << *output;
  }

  return 0;
}
