#include "pico_ssd1306/renderer.h"
#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/helpers.h"
#include <string.h>

void __load_bitarray_from_flat_bitmap(uint8_t bitmap[], uint8_t width,
                                      uint8_t height,
                                      uint8_t output[height][width]) {
    uint8_t row_ind = 0;
    uint8_t col_ind = 0;

    const uint16_t bitmap_length = (width * height) / 8;

    for (int byte_ind = 0; byte_ind < bitmap_length; byte_ind++) {
        for (int i = 0; i < 8; i++) {
            output[row_ind][col_ind] = (bitmap[byte_ind] >> i) & 1;
            col_ind += 1;
        }

        if (col_ind % width == 0) {
            row_ind += 1;
            col_ind = 0;
        }
    }
}

void __insert_bitmap_into_frame(
    SSD1306_Frame* frame, uint8_t x, uint8_t y, uint8_t bitarray_width,
    uint8_t bitarray_height,
    uint8_t bitarray[bitarray_height][bitarray_width]) {

    if (y + bitarray_height >= PICO_SSD1306_HEIGHT) {
        return;
    }

    if (x + bitarray_width >= PICO_SSD1306_WIDTH) {
        return;
    }

    for (int h = 0; h < bitarray_height; h++) {
        for (int w = 0; w < bitarray_width; w++) {
            const uint8_t frame_y = h + y;
            const uint8_t frame_x = w + x;

            frame->bitmap[frame_y][frame_x] = bitarray[h][w];
        }
    }
}

void __convert_frame_to_columns_segments(
    SSD1306_Frame* frame, uint8_t output[],
    uint16_t output_buff_length) {

    const uint16_t flattened_buff_length =
        (PICO_SSD1306_HEIGHT * PICO_SSD1306_WIDTH) / 8;

    int output_item_ind = 0;

    for (int row_page_ind = 0; row_page_ind < PICO_SSD1306_NUM_PAGES;
         row_page_ind++) {
        const int row_start_ind = row_page_ind * 8;

        for (int col_ind = 0; col_ind < PICO_SSD1306_WIDTH; col_ind++) {
            uint8_t byte = 0x00;

            for (int bit_ind = 0; bit_ind < PICO_SSD1306_PAGE_HEIGHT;
                 bit_ind++) {
                byte |= frame->bitmap[row_start_ind + bit_ind][col_ind] << bit_ind;
            }

            output[output_item_ind] = byte;
            output_item_ind++;
        }
    }
}
