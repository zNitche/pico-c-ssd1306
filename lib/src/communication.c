#include "pico_ssd1306/communication.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/types.h"
#include <stdlib.h>
#include <string.h>

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

void _send_commands(SSD1306_I2C i2c_c, uint8_t cmds[], int commands_count) {
    for (int cmd_ind = 0; cmd_ind < commands_count; cmd_ind++) {
        _write_to_reg(i2c_c, PICO_SSD1306_CMD_REG_ADDRESS, cmds[cmd_ind]);
    }
}

void _send_buffer(SSD1306_I2C i2c_c, uint8_t buffer[], int bufflen) {
    const int write_buff_length = bufflen + 1;
    uint8_t* write_buff = malloc(write_buff_length);

    write_buff[0] = PICO_SSD1306_CONTROL_BYTE_ADDRESS;
    memcpy(write_buff + 1, buffer, bufflen);

    i2c_write_blocking(i2c_c.i2c, i2c_c.device_address, write_buff,
                       write_buff_length, false);

    free(write_buff);
}
