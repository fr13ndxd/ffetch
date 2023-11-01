#include "./ascii.cpp"
#include "./sysinfo.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sol/sol.hpp>
#include <string>

std::string default_config = R"(
config = { 
    -- options
}
)";

std::string replace(std::string str, const std::string &search,
                    const std::string &replace) {
  size_t pos = 0;
  while ((pos = str.find(search, pos)) != std::string::npos) {
    str.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return str;
}

std::string replaceVars(std::string str) {
  // colors
  std::map<std::string, std::string> colors = {
      {"1", "\033[31m"},   // Red
      {"2", "\033[32m"},   // Green
      {"3", "\033[34m"},   // Blue
      {"4", "\033[37m"},   // White
      {"5", "\033[35m"},   // Purple
      {"6", "\033[36m"},   // Cyan
      {"7", "\033[33m"},   // Yellow
      {"8", "\033[30m"},   // Black
      {"9", "\033[91m"},   // Light Red
      {"10", "\033[92m"},  // Light Green
      {"11", "\033[94m"},  // Light Blue
      {"12", "\033[97m"},  // Light White
      {"reset", "\033[0m"} // Reset color
  };

  for (const auto &entry : colors) {
    str = replace(str, "$(color " + entry.first + ")", entry.second);
  }
  for (const auto &entry : colors) {
    str = replace(str, "$(c" + entry.first + ")", entry.second);
  }

  // vars
  std::vector<std::pair<std::string, std::string>> vars = {
      {"$(distro)", distroName()}, {"$(distroId)", distroId()},
      {"$(kernel)", kernel()},     {"$(wm)", wm()},
      {"$(shell)", shell()},       {"$(term)", terminal()},
      {"$(ram)", ram()},           {"$(uptime)", uptime()}};

  for (const auto &entry : vars) {
    str = replace(str, entry.first, entry.second);
  }

  return str;
}

int main(int argc, char *argv[]) {
  std::string configDir = "/home/" + std::string(USER()) + "/.config/ffetch/";
  std::string configFile = configDir + "config.lua";
  std::fstream cfg(configFile);

  if (!cfg) {
    std::filesystem::create_directory(configDir);
    cfg.open(configFile, std::ios::out);
    if (cfg) {
      cfg << default_config;
      cfg.close();
      cfg.open(configFile, std::ios::in);
    }
  }

  sol::optional<std::string> ascii;

  try {
    sol::state state;
    state.open_libraries(sol::lib::base, sol::lib::package);
    state.script_file(configFile);
    sol::state_view st(state.lua_state());
    sol::table config = st["config"];

    ascii = config.get<sol::optional<std::string>>("ascii");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  if (!ascii) {
    std::string output = replaceVars(ascii_logo());
    std::cout << output << std::endl;
  } else if (ascii) {
    std::string output = replaceVars(*ascii);
    std::cout << output << std::endl;
  }
}
