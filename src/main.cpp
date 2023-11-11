#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sol/sol.hpp>
#include <string>
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
    "   -h, --help     Print this help and exit\n"
    "   -v, --version  Print version and exit\n"
    "   --ascii-distro Which distro ascii art to print\n"
    "   -c, --config   Path to config file. Default: /home/" +
    std::string(USER()) + "/.config/ffetch/config.lua";

int main(int argc, char *argv[]) {
  if (!std::filesystem::exists(configFile)) {
    std::filesystem::create_directories(
        std::filesystem::path(configFile).parent_path());
    std::ofstream cfg(configFile);
    if (cfg.is_open()) {
      cfg << default_config;
    }
  }

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
    std::cout << *output << std::endl;
  } /*else if (output) {
    std::string output = replaceVars(*output);
    std::cout << output << std::endl;
  } */

  return 0;
}
