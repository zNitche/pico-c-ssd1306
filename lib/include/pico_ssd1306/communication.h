#pragma once

#include "pico_ssd1306/types.h"

void _ssd1306_write_to_reg(SSD1306_I2C i2c_c, uint8_t reg_address,
                           uint8_t buffer[], uint16_t bufflen);
void _ssd1306_read_from_reg(SSD1306_I2C i2c_c, uint8_t reg, int bytes_to_read,
                            uint8_t* buff);
void _ssd1306_send_commands(SSD1306_I2C i2c_c, uint8_t cmds[],
                            int commands_count);
