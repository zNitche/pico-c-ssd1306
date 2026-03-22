import argparse
from PIL import Image


MAX_IMG_WIDTH = 128
MAX_IMG_HEIGHT = 64

BITS_PER_BYTE = 8


def __create_columns(pixels: list[int],
                     img_width: int, img_height: int) -> list[list[int]]:

    bits_columns_segments: list[list[int]] = []

    for columns_row_id in range(img_height // BITS_PER_BYTE):
        column_start_offset = columns_row_id * BITS_PER_BYTE

        for column_index in range(img_width):
            column_bits: list[int] = []

            column_start_bit_index = column_start_offset + \
                (column_index * img_width)

            for bit_index in range(BITS_PER_BYTE):
                target_bit_index = column_start_bit_index + bit_index
                column_bits.append(pixels[target_bit_index])

            bits_columns_segments.append(column_bits)

    return bits_columns_segments


def __create_bitmap(bits_columns_segments: list[list[int]]) -> list[str]:
    output_buffer: list[str] = []

    for column_segment in bits_columns_segments:
        segment_byte = 0

        for bit_index, bit in enumerate(column_segment):
            segment_byte |= (bit << bit_index)

        output_buffer.append(f'{segment_byte:#04x}')

    return output_buffer


def __dump_to_file(img_width: int, img_height: int, output_buffer: list[str], output_path: str):
    with open(output_path, "w") as out_file:
        out_file.write(f"#define bitmap_width {img_width}\n")
        out_file.write(f"#define bitmap_height {img_height}\n")

        out_file.write("\n")

        out_file.write(
            f"static unsigned char bitmap_bits[] = {{ {', '.join(output_buffer)} }};")


def main(args: argparse.Namespace):
    img_path = args.input
    output_path = args.output

    print(f"opening {img_path}")
    pil_img = Image.open(img_path)

    img_width, img_height = pil_img.size

    if img_width > MAX_IMG_WIDTH or img_height > MAX_IMG_HEIGHT:
        raise Exception(
            f"max supported resolution {MAX_IMG_WIDTH}x{MAX_IMG_HEIGHT}, got {img_width}x{img_height}")

    print("converting to b/w...")
    bw_img = pil_img.convert(mode="1")
    bw_img_pixels_data = bw_img.get_flattened_data()

    if (len(bw_img_pixels_data) != img_width * img_height):
        raise Exception(
            f"wrong pixels count, got {len(bw_img_pixels_data)}, got {img_width * img_height}")

    print("normalizing pixels...")
    # values are reversed use black for 1 and white for 0
    normalized_pixels = [0 if pixel ==
                         255 else 1 for pixel in bw_img_pixels_data]  # type: ignore

    print("creating columns segments...")
    bits_columns_segments: list[list[int]] = __create_columns(
        normalized_pixels, img_width, img_height)

    print(f"got {len(bits_columns_segments)} total columns")

    print("creating bitmap...")
    output_buffer: list[str] = __create_bitmap(bits_columns_segments)

    print(f"dumped {len(output_buffer)} bytes")
    print(f"saving to {output_path} ...")

    __dump_to_file(img_width, img_height, output_buffer, output_path)
    print("done.")


def get_args():
    argument_parser = argparse.ArgumentParser()

    argument_parser.add_argument(
        "--input", type=str, help="path to image file", required=True)
    argument_parser.add_argument(
        "--output", type=str, help="path to output bitmap", required=True)

    return argument_parser.parse_args()


if __name__ == "__main__":
    main(get_args())
