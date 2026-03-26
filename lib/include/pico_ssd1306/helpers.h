#pragma once

#include "pico/stdlib.h"

void __byte_to_bits(uint8_t byte, uint8_t bits[8]);
uint8_t __bits_to_byte(uint8_t bits[8]);
