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

    SSD1306_Frame frame;
    ssd1306_prepare_frame(&frame);

    printf("frame prepared, size: %d bytes\n", sizeof(frame));

    SSD1306_Bitmap test_bitmap = {.width = 32, .height = 32, .data = NULL};
    ssd1306_load_bitmap(ssd1306_test_bitmap, &test_bitmap);

    printf("loaded test bitmap, size: %d bytes\n", sizeof(test_bitmap));

    ssd1306_insert_bitmap(&frame, 12, 3, &test_bitmap);
    // ssd1306_insert_bitmap(&frame, 68, 12, &test_bitmap);
    
    char text[] = "Hello World";
    ssd1306_render_string(&frame, 0, 46, text, 3);

    printf("rendering...\n");

    ssd1306_render(ssd1306_i2c, &frame);
    printf("rendered\n");

    sleep_ms(3000);
    ssd1306_display_off(ssd1306_i2c);
    sleep_ms(3000);
    ssd1306_display_on(ssd1306_i2c);

    ssd1306_insert_bitmap(&frame, 68, 12, &test_bitmap);

    ssd1306_render(ssd1306_i2c, &frame);
}
