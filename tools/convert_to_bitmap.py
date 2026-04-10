import argparse
import os
from common import dump_to_file, get_args, BITS_PER_BYTE, MAX_IMG_HEIGHT, MAX_IMG_WIDTH
from PIL import Image


def __create_bitmap(pixels: list[int]) -> list[str]:
    output_buffer: list[str] = []

    for byte_start_index in range( 0, len(pixels), BITS_PER_BYTE):
        current_byte = 0

        for bit_id in range(BITS_PER_BYTE):
            bit_index = byte_start_index + bit_id

            current_byte |= (pixels[bit_index] << bit_id)

        output_buffer.append(f'{current_byte:#04x}')
            

    return output_buffer


def main(args: argparse.Namespace):
    img_path = args.input
    output_path = args.output
    dump_to_h = args.to_h
    output_file_name = args.output_file_name

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

    print("creating bitmap...")
    output_buffer: list[str] = __create_bitmap(normalized_pixels)

    print(f"dumped {len(output_buffer)} bytes")
    print(f"saving to {output_path} ...")

    if not os.path.isdir(output_path):
        raise Exception(f"{output_path} is not a directory")

    dump_to_file(img_width, img_height, output_buffer,
                 output_path, dump_to_h, name_override=output_file_name)
    print("done.")


if __name__ == "__main__":
    main(get_args())
