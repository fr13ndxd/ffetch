#include <algorithm>
#include <fstream>
#include <iostream>

std::string distro_Name() {
  std::ifstream osRelease("/etc/os-release");
  std::string line, name;
  while (std::getline(osRelease, line)) {
    if (line.find("NAME=") == 0) {
      name = line.substr(line.find("=") + 1);
      name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
      return name;
    }
  }
  return " ";
}

std::string ascii_logo(std::string distro = distro_Name()) {
  distro_Name();
  if (distro == "Arch Linux") {
    return R"(
$(color 6)      /\        $(color 4) distro: $(distro)
$(color 6)     /  \       $(color 4) kernel: $(kernel)
$(color 6)    /\   \      $(color 4) wm: $(wm)
$(color 4)   /      \     $(color 4) shell: $(shell)
$(color 4)  /   ,,   \    $(color 4) terminal: $(term)
$(color 4) /   |  |  -\   $(color 4) ram: $(ram)
$(color 4)/_-''    ''-_\  $(color 4) uptime: $(uptime)
$(color 4)                $(color reset)
        )";
  } else if (distro == "EndeavourOS") {
    return R"(
      $(c1)/$(c4)\\       $(c4) distro: $(distro)
    $(c1)/$(c4)/  \\$(c6)\\    $(c4) kernel: $(kernel)
   $(c1)/$(c4)/    \\ $(c6)\\  $(c4) wm: $(wm)
 $(c1)/ $(c4)/     _) $(c6))   $(c4) shell: $(shell)
$(c1)/_$(c4)/___-- $(c6)__-    $(c4) terminal: $(term)
 $(c6)/____--        $(c4) uptime: $(uptime) $(creset)
    )";

  } else {
    return R"(
$(color 8)        #####         $(color 4) distro: $(distro)
$(color 8)       #######        $(color 4) kernel: $(kernel)
$(color 8)       ##$(color 4)O$(color 8)#$(color 4)O$(color 8)##        $(color 4) wm: $(wm)
$(color 8)       #$(color 7)#####$(color 8)#        $(color 4) shell: $(shell)
$(color 8)     ##$(color 4)##$(color 7)###$(color 4)##$(color 8)##      $(color 4) terminal: $(term)
$(color 8)    #$(color 4)##########$(color 8)##     $(color 4) ram: $(ram)
$(color 8)   #$(color 4)############$(color 8)##    $(color 4) uptime: $(uptime)
$(color 8)   #$(color 4)############$(color 8)###   
$(color 7)  ##$(color 8)#$(color 4)###########$(color 8)##$(color 7)#   
$(color 7)######$(color 8)#$(color 4)#######$(color 8)#$(color 7)###### 
$(color 7)#######$(color 8)#$(color 4)#####$(color 8)#$(color 7)####### 
$(color 7)  #####$(color 8)#######$(color 7)#####$(color reset)
    )";
  }
}
