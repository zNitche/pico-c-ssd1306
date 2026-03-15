#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/types.h"

void _write_to_reg(SSD1306_I2C i2c_c, uint8_t reg, uint8_t buff) {
    uint8_t write_buff[2] = {reg, buff};

    i2c_write_blocking(i2c_c.i2c, i2c_c.device_address, write_buff,
                       sizeof(write_buff), false);
}

void _read_from_reg(SSD1306_I2C i2c_c, uint8_t reg, int bytes_to_read,
                    uint8_t* buff) {
    i2c_write_blocking(i2c_c.i2c, i2c_c.device_address, &reg, 1, true);
    i2c_read_blocking(i2c_c.i2c, i2c_c.device_address, buff, bytes_to_read,
                      false);
}
