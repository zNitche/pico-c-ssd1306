#pragma once

#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/types.h"

void __load_bitarray_from_flat_bitmap(uint8_t bitmap[], uint8_t width,
                                      uint8_t height,
                                      uint8_t output[height][width]);
void __insert_bitmap_into_frame(
    SSD1306_Frame* frame, uint8_t x, uint8_t y, uint8_t bitarray_width,
    uint8_t bitarray_height, uint8_t bitarray[bitarray_height][bitarray_width]);
void __convert_frame_to_columns_segments(SSD1306_Frame* frame, uint8_t output[],
                                         uint16_t output_buff_length);
