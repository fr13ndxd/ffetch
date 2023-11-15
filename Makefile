CC = g++
# SRC = rc/sysinfo/terminal/terminal.cpp src/sysinfo/cpu/cpu.cpp src/sysinfo/host/host.cpp src/sysinfo/hostname/hostname.cpp
SRC = src/sysinfo/ram/ram.cpp src/sysinfo/distro/distro.cpp src/sysinfo/kernel/kernel.cpp src/sysinfo/wm/wm.cpp src/sysinfo/distro_id/distro_id.cpp src/sysinfo/uptime/uptime.cpp src/sysinfo/shell/shell.cpp src/sysinfo/user.cpp src/sysinfo/terminal/terminal.cpp src/sysinfo/cpu/cpu.cpp src/sysinfo/host/host.cpp src/sysinfo/hostname/hostname.cpp src/ascii/ascii.cpp src/main.cpp
MAIN = src/main.cpp
OUTPUT = ffetch

$(OUTPUT): $(SRC)
	$(CC) -o $(OUTPUT) $(SRC) $(MAIN) -Ofast

install:
	sudo mv $(OUTPUT) /usr/bin/ffetch
	sudo mkdir /usr/share
	sudo cp -r src/ascii/ /usr/share/ffetch/
	sudo chown ${current_user}:${current_user} /usr/share/ffetch/ascii/
	sudo chmod -R a+r /usr/share/ffetch
	sudo chown ${current_user}:${current_user} /usr/share/ffetch/ascii/

uninstall:
	sudo rm -rf /usr/bin/ffetch
