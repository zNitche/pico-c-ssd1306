#include <stdlib.h>
#include <string.h>

#include "pico_ssd1306/defines.h"
#include "pico_ssd1306/helpers.h"
#include "pico_ssd1306/renderer.h"

void _ssd1306_init_bitmap(SSD1306_Bitmap* bitmap) {
    bitmap->data = malloc(bitmap->height * sizeof(uint8_t*));

    for (int row_ind = 0; row_ind < bitmap->height; row_ind++) {
        bitmap->data[row_ind] = malloc(bitmap->width * sizeof(uint8_t));
    }
}

void _ssd1306_load_bitarray_from_flat_bitmap(uint8_t* bitmap,
                                             SSD1306_Bitmap* output) {
    uint8_t row_ind = 0;
    uint8_t col_ind = 0;

    const uint16_t bitmap_length = (output->width * output->height) / 8;

    for (int byte_ind = 0; byte_ind < bitmap_length; byte_ind++) {
        for (int i = 0; i < 8; i++) {
            output->data[row_ind][col_ind] = (bitmap[byte_ind] >> i) & 1;
            col_ind += 1;
        }

        if (col_ind % output->width == 0) {
            row_ind += 1;
            col_ind = 0;
        }
    }
}

void _ssd1306_insert_bitmap_into_frame(SSD1306_Frame* frame, uint8_t x,
                                       uint8_t y, SSD1306_Bitmap* bitmap) {

    if (y + bitmap->height >= PICO_SSD1306_HEIGHT) {
        return;
    }

    if (x + bitmap->width >= PICO_SSD1306_WIDTH) {
        return;
    }

    for (int h = 0; h < bitmap->height; h++) {
        for (int w = 0; w < bitmap->width; w++) {
            const uint8_t frame_y = h + y;
            const uint8_t frame_x = w + x;

            frame->bitmap[frame_y][frame_x] = bitmap->data[h][w];
        }
    }
}

void _ssd1306_convert_frame_to_columns_segments(SSD1306_Frame* frame,
                                                uint8_t output[],
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
                byte |= frame->bitmap[row_start_ind + bit_ind][col_ind]
                        << bit_ind;
            }

            output[output_item_ind] = byte;
            output_item_ind++;
        }
    }
}
