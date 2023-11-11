#include "./config.h"

sol::state state;

config::config(const std::string &configFile) {
  state.open_libraries(sol::lib::base, sol::lib::package);
  state.script_file(configFile);
  sol::state_view st(state.lua_state());
  sol::table luaConfig = st["config"];
  if (!ascii_art) {
    ascii_art = luaConfig.get<sol::optional<std::string>>("ascii");
  }
  ascii_distro = luaConfig.get<std::string>("ascii_distro");
}
