file(GLOB PICO_SSD1306_EXECS ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

cmake_minimum_required(VERSION 3.27)

project(pico_ssd1306 VERSION 0.0.1)

add_library(pico_ssd1306 INTERFACE)

target_link_libraries(pico_ssd1306 INTERFACE
  pico_stdlib
  hardware_i2c
)

target_include_directories(pico_ssd1306 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_sources(pico_ssd1306 INTERFACE ${PICO_SSD1306_EXECS})
