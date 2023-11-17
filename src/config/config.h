#ifndef CONFIG_H
#define CONFIG_H

#include <sol/sol.hpp>
#include <string>

class config {
public:
  sol::optional<std::string> ascii_art;
  std::string ascii_distro;
  bool shell_path;

  config(const std::string &configFile);
};

#endif
