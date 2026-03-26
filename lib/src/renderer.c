#include "pico_ssd1306/renderer.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/helpers.h"
#include <string.h>

void __load_bitarray_from_flat_bitmap(uint8_t bitmap[], uint8_t width,
                                      uint8_t height,
                                      uint8_t output[height][width]) {
    int row_ind = 0;
    const uint8_t bitmap_length = width * height;

    for (int byte_ind = 0; byte_ind < bitmap_length; byte_ind++) {
        uint8_t bits[8] = {0};
        __byte_to_bits(bitmap[byte_ind], bits);

        for (int i = 0; i < 8; i++) {
            output[row_ind][i + (byte_ind * 8)] = bits[i];
        }

        if (byte_ind % width == 0) {
            row_ind++;
        }
    }
}

void __convert_frame_to_columns_segments(
    uint8_t frame[PICO_SSD1306_HEIGHT][PICO_SSD1306_WIDTH], uint8_t* output,
    uint16_t output_buff_length) {

    const uint16_t flattened_buff_length =
        (PICO_SSD1306_HEIGHT * PICO_SSD1306_WIDTH) / 8;

    int output_item_ind = 0;

    for (int row_page_ind = 0; row_page_ind < PICO_SSD1306_NUM_PAGES; row_page_ind++) {
        const int row_start_ind = row_page_ind * 8; 

        for (int col_ind = 0; col_ind < PICO_SSD1306_WIDTH; col_ind++) {
            uint8_t byte = 0x00;

            for (int bit_ind = 0; bit_ind < PICO_SSD1306_PAGE_HEIGHT; bit_ind++) {
                byte |= frame[row_start_ind + bit_ind][col_ind] << bit_ind;
            }

            output[output_item_ind] = byte;
            output_item_ind++;
        }
    }
}
