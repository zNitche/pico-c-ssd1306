#pragma once

#include "hardware/i2c.h"

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
