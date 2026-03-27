#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico_ssd1306/bitmaps/ssd1306_test_bitmap.h"
#include "pico_ssd1306/bitmaps/ssd1306_test_segmented_bitmap.h"
#include "pico_ssd1306/ssd1306.h"

int main() {
    stdio_init_all();

#ifdef DEBUG
    // waiting for input
    getchar();
#endif

    SSD1306_I2C ssd1306_i2c = {
        .i2c = i2c0, .device_address = 0x3C, .sda_pin = 0, .scl_pin = 1};

    ssd1306_setup_i2c(ssd1306_i2c);
    sleep_ms(250);
    printf("connected...\n");

    ssd1306_init(ssd1306_i2c);
    printf("ssd1306 init done...\n");

    ssd1306_clear(ssd1306_i2c);
    printf("ssd1306 screen cleared...\n");

    // ssd1306_render_simple_bitmap(ssd1306_i2c, 48, 8,
    //                              ssd1306_test_segmented_bitmap, 32, 32);

    ssd1306_render_bitmap(ssd1306_i2c, 12, 3, ssd1306_test_bitmap, 32, 32);
    sleep_ms(3000);
    ssd1306_render_bitmap(ssd1306_i2c, 68, 12, ssd1306_test_bitmap, 32, 32);
}
