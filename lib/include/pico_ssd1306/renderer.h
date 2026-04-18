#pragma once

#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/types.h"

void _ssd1306_init_bitmap(SSD1306_Bitmap* bitmap);
void _ssd1306_load_bitarray_from_flat_bitmap(uint8_t* bitmap,
                                             SSD1306_Bitmap* output);
void _ssd1306_insert_bitmap_into_frame(SSD1306_Frame* frame, uint8_t x,
                                       uint8_t y, SSD1306_Bitmap* bitmap);
void _ssd1306_convert_frame_to_columns_segments(SSD1306_Frame* frame,
                                                uint8_t output[],
                                                uint16_t output_buff_length);
