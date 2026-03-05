cmake_minimum_required(VERSION 3.27)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_ssd1306_example VERSION 0.0.1)

pico_sdk_init()

add_executable(example src/example.c)

if (DEBUG)
    target_compile_definitions(example PUBLIC DEBUG=1)

    target_link_libraries(example
        pico_bootsel_via_double_reset
        )
endif()

target_link_libraries(example
        pico_stdlib
        )

pico_enable_stdio_uart(example 0)
pico_enable_stdio_usb(example 1)

pico_add_extra_outputs(example)
