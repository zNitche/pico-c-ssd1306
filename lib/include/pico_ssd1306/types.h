#pragma once

#include "hardware/i2c.h"
#include "pico_ssd1306/defines.h"

typedef struct {
    i2c_inst_t* i2c;
    int device_address;
    int sda_pin;
    int scl_pin;
} SSD1306_I2C;

typedef struct {
    uint8_t start_column;
    uint8_t end_column;
    uint8_t start_page;
    uint8_t end_page;
    uint8_t* buffer;
    uint16_t bufflen;
} SSD1306_DrawData;

typedef struct {
    uint8_t bitmap[PICO_SSD1306_HEIGHT][PICO_SSD1306_WIDTH];
} SSD1306_Frame;

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t** data;
} SSD1306_Bitmap;
