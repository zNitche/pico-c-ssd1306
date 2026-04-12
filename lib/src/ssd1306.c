#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/font.h"
#include "pico_ssd1306/renderer.h"
#include "pico_ssd1306/ssd1306.h"
#include "pico_ssd1306/ssd1306_commands.h"
#include "pico_ssd1306/types.h"

void ssd1306_setup_i2c(SSD1306_I2C i2c_c) {
    i2c_init(i2c_c.i2c, PICO_SSD1306_I2C_BAUDRATE);

    gpio_set_function(i2c_c.sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(i2c_c.scl_pin, GPIO_FUNC_I2C);

    gpio_pull_up(i2c_c.sda_pin);
    gpio_pull_up(i2c_c.scl_pin);
}

void ssd1306_init(SSD1306_I2C i2c_c) {
    // https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp
    // datasheet page no. 64 - 3. Software Configuration

    uint8_t cmds[] = {
        PICO_SSD1306_BASE_DISPLAY_OFF,

        PICO_SSD1306_SET_MEMORY_ADDRESSING_MODE_REG,
        PICO_SSD1306_SET_MEMORY_HORIZONTAL_ADDRESSING_MODE,

        PICO_SSD1306_SET_DISPLAY_START_LINE,
        PICO_SSD1306_SET_SEGMENT_REMAP_INV,

        PICO_SSD1306_SET_COM_OUTPUT_SCAN_DIRECTION_INV,
        PICO_SSD1306_SET_DISPLAY_OFFSET_REG,
        PICO_SSD1306_SET_DISPLAY_OFFSET,

        PICO_SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_REG,
        PICO_SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION,

        PICO_SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_REG,
        PICO_SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO,

        PICO_SSD1306_SET_PRECHARGE_PERIOD_REG,
        PICO_SSD1306_SET_PRECHARGE_PERIOD,

        PICO_SSD1306_SET_VCOMH_DESELECT_LEVEL_REG,
        PICO_SSD1306_SET_VCOMH_DESELECT_LEVEL_TOP,

        PICO_SSD1306_SET_CONTRAST_CONTROL_REG,
        PICO_SSD1306_SET_CONTRAST_RESET,

        PICO_SSD1306_BASE_ENTIRE_DISPLAY_ON,
        PICO_SSD1306_BASE_SET_NORMAL_DISPLAY,

        PICO_SSD1306_SET_CHARGE_PUMP_SETTING_REG,
        PICO_SSD1306_SET_CHARGE_PUMP_SETTING,

        PICO_SSD1306_SCROLLING_DEACTIVATE_SCROLL,
        PICO_SSD1306_BASE_DISPLAY_ON,
    };

    _send_commands(i2c_c, cmds, count_of(cmds));
}

void _ssd1306_draw(SSD1306_I2C i2c_c, SSD1306_DrawData* draw_data) {
    uint8_t cmds[] = {
        PICO_SSD1306_SET_COLUMN_ADDRESS_REG,
        draw_data->start_column,
        draw_data->end_column,
        PICO_SSD1306_SET_PAGE_ADDRESS_REG,
        draw_data->start_page,
        draw_data->end_page,
    };

    _send_commands(i2c_c, cmds, count_of(cmds));
    _write_to_reg(i2c_c, PICO_SSD1306_CONTROL_BYTE_ADDRESS, draw_data->buffer,
                  draw_data->bufflen);
}

void ssd1306_render(SSD1306_I2C i2c_c, SSD1306_Frame* frame) {
    const uint16_t output_buff_length =
        PICO_SSD1306_NUM_PAGES * PICO_SSD1306_WIDTH;
    uint8_t output_buff[output_buff_length];

    __convert_frame_to_columns_segments(frame, output_buff, output_buff_length);

    SSD1306_DrawData draw_data = {.start_column = 0,
                                  .end_column = PICO_SSD1306_WIDTH - 1,
                                  .start_page = 0,
                                  .end_page = PICO_SSD1306_NUM_PAGES - 1,
                                  .bufflen = output_buff_length,
                                  .buffer = output_buff};

    _ssd1306_draw(i2c_c, &draw_data);
}

void ssd1306_clear(SSD1306_I2C i2c_c) {
    SSD1306_Frame frame = {.bitmap = {0}};

    ssd1306_render(i2c_c, &frame);
}

void ssd1306_prepare_frame(SSD1306_Frame* frame) {
    memset(frame->bitmap, 0, (PICO_SSD1306_WIDTH * PICO_SSD1306_HEIGHT));
}

void ssd1306_render_fast_bitmap(SSD1306_I2C i2c_c, uint8_t x, uint8_t y,
                                uint8_t bitmap[], uint8_t bitmap_width,
                                uint8_t bitmap_height) {
    /// requires columns segmented bitmap -
    /// convert_to_columns_segmented_bitmap.py

    // draw respecting pages, every 8 px
    const uint8_t start_y = y / 8;

    SSD1306_DrawData draw_data = {
        .start_column = x,
        .end_column = x + bitmap_width - 1,
        .start_page = start_y,
        .end_page = start_y + (bitmap_height / PICO_SSD1306_PAGE_HEIGHT - 1),
        .buffer = bitmap,
        .bufflen = bitmap_width * bitmap_height / 8};

    _ssd1306_draw(i2c_c, &draw_data);
}

void ssd1306_load_bitmap(uint8_t* raw_bitmap, SSD1306_Bitmap* target_bitmap) {
    __init_bitmap(target_bitmap);
    __load_bitarray_from_flat_bitmap(raw_bitmap, target_bitmap);
}

void ssd1306_insert_bitmap(SSD1306_Frame* frame, uint8_t x, uint8_t y,
                           SSD1306_Bitmap* bitmap) {
    __insert_bitmap_into_frame(frame, x, y, bitmap);
}

void ssd1306_render_character(SSD1306_Frame* frame, uint8_t x, uint8_t y,
                              char character) {
    SSD1306_Bitmap char_bitmap = {.width = 8, .height = 8, .data = NULL};

    int char_index = (int)toupper(character);

    uint8_t char_buff[8] = {0};
    memcpy(char_buff, font[char_index - 32], 8);

    ssd1306_load_bitmap(char_buff, &char_bitmap);

    ssd1306_insert_bitmap(frame, x, y, &char_bitmap);
}
