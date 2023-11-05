#include "./ascii.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sol/sol.hpp>
#include <string>

#define ANSI_SAVE_CURSOR "\033[s"
#define ANSI_RESTORE_CURSOR "\033[u"
#define ANSI_CLEAR_LINE "\033[K"

// system info
// TODO: add host, packages, display, cursor, gpu, disk, battery, locale
#include "./sysinfo/cpu/cpu.h"
#include "./sysinfo/distro/distro.h"
#include "./sysinfo/distro_id/distro_id.h"
#include "./sysinfo/host/host.h"
#include "./sysinfo/hostname/hostname.h"
#include "./sysinfo/kernel/kernel.h"
#include "./sysinfo/ram/ram.h"
#include "./sysinfo/shell/shell.h"
#include "./sysinfo/terminal/terminal.h"
#include "./sysinfo/uptime/uptime.h"
#include "./sysinfo/user.h"
#include "./sysinfo/wm/wm.h"

std::string version = "0.1";
std::string default_config = R"(
config = { 
    -- options
}
)";

std::string help_message =
    "OPTIONS:\n"
    "   -h, --help     Print this help and exit\n"
    "   -v, --version  Print version and exit\n"
    "   --ascii-distro Which distro ascii art to print\n"
    "   -c, --config   Path to config file. Default: /home/" +
    std::string(USER()) + "/.config/ffetch/config.lua";

std::string replace(std::string str, const std::string &search,
                    const std::string &replace) {
  size_t lastPos = 0;
  size_t findPos;
  while ((findPos = str.find(search, lastPos)) != std::string::npos) {
    str.replace(findPos, search.length(), replace);
    lastPos = findPos + replace.length();
  }
  return str;
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
      {"$(shell)", shell()},   {"$(term)", terminal()},
      {"$(ram)", ram()},       {"$(uptime)", uptime()},
      {"$(cpu)", cpu()},       {"$(user)", USER()},
      {"$(host)", host()},     {"$(hostname)", hostname()}};

  for (const auto &entry : vars) {
    str = replace(str, entry.first, entry.second);
  }

  return str;
}

int main(int argc, char *argv[]) {
  std::string configDir = "/home/" + std::string(USER()) + "/.config/ffetch/";
  std::string configFile = configDir + "config.lua";
  sol::optional<std::string> ascii;
  std::fstream cfg(configFile);

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
        ascii = ascii_logo(argv[i + 1]);
      }
    }
  }

  if (!cfg) {
    std::filesystem::create_directory(configDir);
    cfg.open(configFile, std::ios::out);
    if (cfg) {
      cfg << default_config;
      cfg.close();
      cfg.open(configFile, std::ios::in);
    }
  }

  try {
    sol::state state;
    state.open_libraries(sol::lib::base, sol::lib::package);
    state.script_file(configFile);
    sol::state_view st(state.lua_state());
    sol::table config = st["config"];
    if (!ascii) {
      ascii = config.get<sol::optional<std::string>>("ascii");
    }
    std::string ascii_distro = config.get<std::string>("ascii_distro");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  if (!ascii) {
    std::string output = replaceVars(ascii_logo());
    std::cout << output << std::endl;
  } else if (ascii) {
    std::string output = replaceVars(*ascii);
    std::cout << output << std::endl;
  }
}
