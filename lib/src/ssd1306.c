#include "pico_ssd1306/ssd1306.h"
#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/ssd1306_commands.h"

#include "hardware/i2c.h"
#include "pico/stdlib.h"

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
        PICO_SSD1306_SET_MULTIPLEX_RATIO_REG,
        PICO_SSD1306_HEIGHT - 1,
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

    for (int cmd_ind = 0; cmd_ind < count_of(cmds); cmd_ind++) {
        _write_to_reg(i2c_c, PICO_SSD1306_CMD_REG_ADDRESS, cmds[cmd_ind]);
    }
}
