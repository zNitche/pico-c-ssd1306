#pragma once

#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/types.h"

void __load_bitarray_from_flat_bitmap(uint8_t bitmap[], uint8_t width,
                                      uint8_t height,
                                      uint8_t output[height][width]);
void __convert_frame_to_columns_segments(
    uint8_t frame[PICO_SSD1306_HEIGHT][PICO_SSD1306_WIDTH], uint8_t* output,
    uint16_t output_buff_length);
