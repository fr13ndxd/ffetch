#include "./sysinfo/distro/distro.h"
#include <algorithm>
#include <fstream>
#include <iostream>

std::string ascii_logo(std::string os = distro()) {
  if (os == "Arch Linux") {
    return R"(
$(c6)      /\        $(c4) distro: $(distro)
$(c6)     /  \       $(c4) kernel: $(kernel)
$(c6)    /\   \      $(c4) wm: $(wm)
$(c4)   /      \     $(c4) shell: $(shell)
$(c4)  /   ,,   \    $(c4) terminal: $(term)
$(c4) /   |  |  -\   $(c4) ram: $(ram)
$(c4)/_-''    ''-_\  $(c4) uptime: $(uptime)
$(c4)                $(cr)
        )";
  } else if (os == "EndeavourOS") {
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
