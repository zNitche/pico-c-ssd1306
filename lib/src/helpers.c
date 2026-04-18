#include "pico_ssd1306/helpers.h"

void _ssd1306_byte_to_bits(uint8_t byte, uint8_t bits[8]) {
    for (int i = 0; i < 8; i++) {
        bits[i] = (byte >> i) & 1;
    }
}

uint8_t _ssd1306_bits_to_byte(uint8_t bits[8]) {
    uint8_t output_byte = 0;

    for (int i = 0; i < 8; i++) {
        output_byte = (output_byte << 1) | (bits[i] & 1);
    }

    return output_byte;
}
