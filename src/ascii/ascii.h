#ifndef ASCII_H
#define ASCII_H
#include "../sysinfo/distro/distro.h"
#include <string>

std::string ascii(std::string os = distro(), bool ascii_always_small = false);


#endif
