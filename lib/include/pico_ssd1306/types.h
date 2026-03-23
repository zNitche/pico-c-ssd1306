#pragma once

#include "hardware/i2c.h"

typedef struct {
    i2c_inst_t* i2c;
    int device_address;
    int sda_pin;
    int scl_pin;
} SSD1306_I2C;

typedef struct {
    int start_column;
    int end_column;
    int start_page;
    int end_page;
    uint8_t* bitmap;
    int bufflen;
} SSD1306_DrawData;
