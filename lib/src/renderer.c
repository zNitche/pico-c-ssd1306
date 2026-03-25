#include "pico_ssd1306/renderer.h"
#include "pico_ssd1306/defines.h"
#include <string.h>

void __flatten_frame(uint8_t frame[PICO_SSD1306_HEIGHT][PICO_SSD1306_WIDTH],
                     uint8_t* output, uint16_t output_buff_length) {

    memset(output, 0x00, output_buff_length);

    for (int row_ind = 0; row_ind < PICO_SSD1306_HEIGHT; row_ind++) {
        const int ind_offset = row_ind * PICO_SSD1306_WIDTH;

        for (int column_ind = 0; column_ind < PICO_SSD1306_WIDTH;
             column_ind++) {
            output[ind_offset + column_ind] = frame[row_ind][column_ind];
        }
    }
}

void __convert_frame_to_columns_segments(
    uint8_t frame[PICO_SSD1306_HEIGHT][PICO_SSD1306_WIDTH], uint8_t* output,
    uint16_t output_buff_length) {

    const uint16_t flattened_buff_length =
        PICO_SSD1306_HEIGHT * PICO_SSD1306_WIDTH;

    uint8_t flattened_buff[flattened_buff_length];
    __flatten_frame(frame, flattened_buff, flattened_buff_length);

    memset(output, 0x00, output_buff_length);

    int output_item_ind = 0;

    for (int col_ind = 0; col_ind < PICO_SSD1306_NUM_PAGES; col_ind++) {
        const uint8_t column_start_index =
            col_ind * PICO_SSD1306_WIDTH * PICO_SSD1306_PAGE_HEIGHT;

        for (int row_ind = 0; row_ind < PICO_SSD1306_WIDTH; row_ind++) {
            uint8_t byte = 0x00;

            for (int bit_ind = 0; bit_ind < PICO_SSD1306_PAGE_HEIGHT;
                 bit_ind++) {

                byte |= flattened_buff[bit_ind * PICO_SSD1306_WIDTH +
                                       column_start_index + row_ind]
                        << bit_ind;
            }

            output[output_item_ind] = byte;
            output_item_ind++;
        }
    }
}
