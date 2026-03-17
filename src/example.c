#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico_ssd1306/ssd1306.h"

int main() {
    stdio_init_all();

#ifdef DEBUG
    // waiting for input
    getchar();
#endif

    SSD1306_I2C ssd1306_i2c = {i2c0, 0x3C, 0, 1};

    ssd1306_setup_i2c(ssd1306_i2c);
    sleep_ms(250);
    printf("connected...\n");

    ssd1306_init(ssd1306_i2c);
    printf("ssd1306 init done...\n");

    ssd1306_clear(ssd1306_i2c);
    printf("ssd1306 screen cleared...\n");
}
