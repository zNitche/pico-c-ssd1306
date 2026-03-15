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
