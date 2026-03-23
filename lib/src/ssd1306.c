#include "pico_ssd1306/ssd1306.h"
#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/ssd1306_commands.h"
#include "pico_ssd1306/types.h"

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <string.h>

void ssd1306_setup_i2c(SSD1306_I2C i2c_c) {
    i2c_init(i2c_c.i2c, 400000);

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

void _ssd1306_raw_render(SSD1306_I2C i2c_c, SSD1306_DrawData* draw_data) {
    uint8_t cmds[] = {
        PICO_SSD1306_SET_COLUMN_ADDRESS_REG,
        draw_data->start_column,
        draw_data->end_column,
        PICO_SSD1306_SET_PAGE_ADDRESS_REG,
        draw_data->start_page,
        draw_data->end_page,
    };

    _send_commands(i2c_c, cmds, count_of(cmds));
    _write_to_reg(i2c_c, PICO_SSD1306_CONTROL_BYTE_ADDRESS, draw_data->bitmap,
                  draw_data->bufflen);
}

void ssd1306_clear(SSD1306_I2C i2c_c) {
    SSD1306_DrawData draw_data = {
        .start_column = 0,
        .end_column = PICO_SSD1306_WIDTH - 1,
        .start_page = 0,
        .end_page = PICO_SSD1306_NUM_PAGES - 1,
        .bufflen = (PICO_SSD1306_WIDTH * PICO_SSD1306_HEIGHT) / 8};

    uint8_t buff[draw_data.bufflen];
    memset(buff, 0x00, draw_data.bufflen);

    draw_data.bitmap = buff;

    _ssd1306_raw_render(i2c_c, &draw_data);
}

void ssd1306_render_bitmap(SSD1306_I2C i2c_c, uint8_t bitmap[], int width,
                           int height) {
    SSD1306_DrawData draw_data = {
        .start_column = 0,
        .end_column = width - 1,
        .start_page = 0,
        .end_page = height / PICO_SSD1306_PAGE_HEIGHT - 1,
        .bitmap = bitmap,
        .bufflen = width * height / 8};

    _ssd1306_raw_render(i2c_c, &draw_data);
}
