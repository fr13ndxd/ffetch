#include "./shell.h"
#include <filesystem>

std::string shell(bool shell_path = false) {
    std::string shell = std::getenv("SHELL");
    if (shell_path) {
      return shell.empty() ? " " : shell;
    } else {
      return shell.empty() ? " " : std::filesystem::path(shell).filename().c_str();
    }
}
