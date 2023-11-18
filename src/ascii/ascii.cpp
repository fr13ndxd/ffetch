#include "../sysinfo/distro/distro.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include "./ascii.h"
#include "./ascii_arts.h"
#include <stdexcept>

std::unordered_map<std::string, std::string> distro_art = {
    {"nixos", nixos},
    {"nixos_small", nixos_small}
};

std::string ascii(std::string os, bool ascii_always_small) {
  if(os.empty()) os = distro();
  std::replace(os.begin(), os.end(), ' ', '_');
  std::transform(os.begin(), os.end(), os.begin(), ::tolower);
  if(ascii_always_small == true) os += "_small";
  // std::cout << os;

  try {
    return distro_art.at(os);
  } catch (const std::out_of_range& e) {
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
}
