#pragma once

#include "pico_ssd1306/types.h"

void ssd1306_setup_i2c(SSD1306_I2C i2c_c);
void ssd1306_init(SSD1306_I2C i2c_c);
void _ssd1306_draw(SSD1306_I2C i2c_c, SSD1306_DrawData* draw_data);
void ssd1306_render(SSD1306_I2C i2c_c, SSD1306_Frame* frame);
void ssd1306_clear(SSD1306_I2C i2c_c);
void ssd1306_prepare_frame(SSD1306_Frame* frame);
void ssd1306_render_fast_bitmap(SSD1306_I2C i2c_c, uint8_t x, uint8_t y,
                                uint8_t bitmap[], uint8_t bitmap_width,
                                uint8_t bitmap_height);
void ssd1306_load_bitmap(uint8_t* raw_bitmap, SSD1306_Bitmap* target_bitmap);
void ssd1306_insert_bitmap(SSD1306_Frame* frame, uint8_t x, uint8_t y,
                           SSD1306_Bitmap* bitmap);
