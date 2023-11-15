#include "./utils.h"
#include "../ascii/ascii.h"
#include <algorithm>
#include <map>
#include <sol/sol.hpp>
#include <string>
#include <vector>

// other
#include "../sysinfo/cpu/cpu.h"
#include "../sysinfo/distro/distro.h"
#include "../sysinfo/distro_id/distro_id.h"
#include "../sysinfo/host/host.h"
#include "../sysinfo/hostname/hostname.h"
#include "../sysinfo/kernel/kernel.h"
#include "../sysinfo/ram/ram.h"
#include "../sysinfo/shell/shell.h"
#include "../sysinfo/terminal/terminal.h"
#include "../sysinfo/uptime/uptime.h"
#include "../sysinfo/user.h"
#include "../sysinfo/wm/wm.h"

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


std::string parseArgs(int argc, char *argv[], std::string &configFile,
                      sol::optional<std::string> &output) {
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
  return 0;
}
