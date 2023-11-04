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
)

set(MAIN src/main.cpp)
set(OUTPUT ffetch)

add_executable(${OUTPUT} ${SRC} ${MAIN})

target_compile_options(${OUTPUT} PRIVATE -Ofast -Wall)

target_link_libraries(${OUTPUT} lua)

install(TARGETS ${OUTPUT} DESTINATION /usr/bin)
install(DIRECTORY src/ascii/ DESTINATION /usr/share/ffetch)
file(GLOB_RECURSE ASSETS src/ascii/*)
install(FILES ${ASSETS} DESTINATION /usr/share/ffetch/ascii/)

execute_process(COMMAND sudo chmod -R a+r /usr/share/ffetch)
execute_process(COMMAND sudo chown ${current_user}:${current_user} /usr/share/ffetch/ascii/)
