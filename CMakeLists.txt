cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)

if (DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
else()
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(PICO_BOARD "pico")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_ssd1306_example VERSION 1.0.1)

pico_sdk_init()

add_subdirectory(lib)
add_executable(example src/example.c)

if (DEBUG)
    message("configuring for Debug...")

    target_compile_definitions(example PUBLIC DEBUG=1)

    target_link_libraries(example
        pico_bootsel_via_double_reset
        )
else()
    message("configuring for Release...")
endif()

target_link_libraries(example
        pico_stdlib
        hardware_i2c
        pico_ssd1306
        )

pico_enable_stdio_uart(example 0)
pico_enable_stdio_usb(example 1)

pico_add_extra_outputs(example)
