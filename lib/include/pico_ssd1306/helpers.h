#pragma once

#include "pico/stdlib.h"

void _ssd1306_byte_to_bits(uint8_t byte, uint8_t bits[8]);
uint8_t _ssd1306_bits_to_byte(uint8_t bits[8]);
