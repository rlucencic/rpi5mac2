# rpi5mac2: the Macintosh LC and II on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5mac2 --help
#
# The Mac itself is esp32mac2's (../esp32mac2/components/mac2, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 68020 and the 68881 (Musashi)
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5mac2 C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32MAC2_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32mac2" CACHE PATH "esp32mac2 checkout: the Mac")
if(NOT EXISTS "${ESP32MAC2_DIR}/components/mac2/include/mac.h")
    message(FATAL_ERROR "No esp32mac2 at ${ESP32MAC2_DIR}: clone github.com/rlucencic/esp32mac2 beside rpi5mac2")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB MAC_SOURCES "${ESP32MAC2_DIR}/components/mac2/*.c")
add_executable(rpi5mac2
    src/main.c
    src/settings.c
    src/rom_store.c
    ${MAC_SOURCES})
target_include_directories(rpi5mac2 PRIVATE
    src
    "${ESP32MAC2_DIR}/components/mac2/include"
    "${ESP32MAC2_DIR}/components/mac2")
# The 68020 (and the II's 68881), as esp32mac2's CONFIG_M68K_68020
target_compile_definitions(rpi5mac2 PRIVATE M68K_68020)
rpi5emu_add_cores(rpi5mac2 musashi diskspace)
# The web page's converters: StuffIt, Compact Pro, BinHex, MacBinary to HFS
# images (esp32mac2's main/web/macfiles.js, LGPL: its COPYING.LGPL)
rpi5emu_embed(rpi5mac2 "${ESP32MAC2_DIR}/main/web/macfiles.js" macfiles_js)
target_link_libraries(rpi5mac2 PRIVATE rpi5emu)
target_compile_options(rpi5mac2 PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS rpi5mac2)
