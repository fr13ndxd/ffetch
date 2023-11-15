cmake_minimum_required(VERSION 3.0)
project(ffetch)

set(CMAKE_CXX_STANDARD 20)

execute_process(COMMAND whoami
               OUTPUT_VARIABLE current_user
               OUTPUT_STRIP_TRAILING_WHITESPACE)

set(SRC
    src/sysinfo/ram/ram.cpp
    src/sysinfo/distro/distro.cpp
    src/sysinfo/kernel/kernel.cpp
    src/sysinfo/wm/wm.cpp
    src/sysinfo/distro_id/distro_id.cpp
    src/sysinfo/uptime/uptime.cpp
    src/sysinfo/shell/shell.cpp
    src/sysinfo/user.cpp
    src/sysinfo/terminal/terminal.cpp
    src/sysinfo/cpu/cpu.cpp
    src/sysinfo/host/host.cpp
    src/sysinfo/hostname/hostname.cpp
    src/config/config.cpp
    src/ascii/ascii.cpp
)

set(MAIN src/main.cpp)
set(OUTPUT ffetch)

add_executable(${OUTPUT} ${SRC} ${MAIN})

target_compile_options(${OUTPUT} PRIVATE -Ofast -Wall)

target_link_libraries(${OUTPUT} lua)
