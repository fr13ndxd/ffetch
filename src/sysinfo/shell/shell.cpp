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


/*
    if (shell != nullptr) {
        std::filesystem::path shellPath(shell);
        std::string shellName = shellPath.filename().string();

        // Convert std::string to char*
        char *shellNameChar = strdup(shellName.c_str());

        std::cout << "Shell: " << shellNameChar << std::endl;

        // Don't forget to free the allocated memory
        free(shellNameChar);
    } else {
        std::cout << "Shell environment variable not set." << std::endl;
    }
*/
