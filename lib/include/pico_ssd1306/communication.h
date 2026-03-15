#pragma once

#include "pico_ssd1306/types.h"

void _write_to_reg(SSD1306_I2C i2c_c, uint8_t reg, uint8_t buff);
void _read_from_reg(SSD1306_I2C i2c_c, uint8_t reg, int bytes_to_read,
                    uint8_t* buff);
