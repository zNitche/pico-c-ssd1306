#include "pico_ssd1306/ssd1306.h"
#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/defines.h"

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
    // datasheet page no. 64 - 3. Software Configuration

    uint8_t cmds[] = {
        0xAE, 0x3F, 0xD3, 0x00, 0x40, 0xA0, 0xA1, 0xC0, 0xC8, 0xDA,
        0x12, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF,
    };

    for (int cmd_ind = 0; cmd_ind < count_of(cmds); cmd_ind++) {
        _write_to_reg(i2c_c, PICO_SSD1306_CMD_REG_ADDRESS, cmds[cmd_ind]);
    }
}
