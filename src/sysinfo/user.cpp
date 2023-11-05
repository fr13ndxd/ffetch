#include "./user.h"
#include <iostream>

std::string USER() { return std::getenv("USER"); }
