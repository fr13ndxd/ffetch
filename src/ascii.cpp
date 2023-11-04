#include "./sysinfo/distro/distro.h"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

std::string ascii_logo(std::string os = distro()) {
  std::replace(os.begin(), os.end(), ' ', '_');
  std::transform(os.begin(), os.end(), os.begin(), ::tolower);
  std::string ascii_dir = "/usr/share/ffetch/ascii/" + os + ".txt";
  std::ifstream ascii_file(ascii_dir);

  if (ascii_file.is_open()) {
    std::stringstream buffer;
    buffer << ascii_file.rdbuf();
    std::string ascii = buffer.str();
    ascii_file.close();

    return ascii;
  }

  return R"(
$(c8)        #####         $(c4) distro: $(distro)
$(c8)       #######        $(c4) kernel: $(kernel)
$(c8)       ##$(c4)O$(c8)#$(c4)O$(c8)##        $(c4) wm: $(wm)
$(c8)       #$(c7)#####$(c8)#        $(c4) shell: $(shell)
$(c8)     ##$(c4)##$(c7)###$(c4)##$(c8)##      $(c4) terminal: $(term)
$(c8)    #$(c4)##########$(c8)##     $(c4) ram: $(ram)
$(c8)   #$(c4)############$(c8)##    $(c4) uptime: $(uptime)
$(c8)   #$(c4)############$(c8)###   
$(c7)  ##$(c8)#$(c4)###########$(c8)##$(c7)#   
$(c7)######$(c8)#$(c4)#######$(c8)#$(c7)###### 
$(c7)#######$(c8)#$(c4)#####$(c8)#$(c7)####### 
$(c7)  #####$(c8)#######$(c7)#####$(cr)

Your distro is not yet included in ascii arts
    )";
}
