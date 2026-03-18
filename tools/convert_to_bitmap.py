import argparse
from PIL import Image


IMG_WIDTH = 128
IMG_HEIGHT = 64

BITS_PER_BYTE = 8


def main(args: argparse.Namespace):
    img_path = args.input
    output_path = args.output

    print(f"opening {img_path}")
    pil_img = Image.open(img_path)

    img_width, img_height = pil_img.size

    if img_width > IMG_WIDTH or img_height > IMG_HEIGHT:
        raise Exception(
            f"max supported resolution {IMG_WIDTH}x{IMG_HEIGHT}, got {img_width}x{img_height}")

    print("converting to b/w...")
    bw_img = pil_img.convert(mode="1")
    bw_img_pixels_data = bw_img.get_flattened_data()

    print("normalizing pixels...")
    normalized_pixels = [0 if pixel ==
                         255 else 1 for pixel in bw_img_pixels_data]  # type: ignore

    output_buffer: list[str] = []

    print("creating bitmap...")

    # split pixels into x rows BITS_PER_BYTE pixels height
    for row_index in range(img_height // BITS_PER_BYTE):
        row_start_index = row_index * img_width * BITS_PER_BYTE

        # iterate over row's columns
        for column_index in range(img_width):
            column_start_offset = row_start_index + column_index
            current_byte = 0

            for bit_index in range(BITS_PER_BYTE):
                pixel_index = (bit_index * img_width) + column_start_offset

                current_byte |= (normalized_pixels[pixel_index] << bit_index)

            output_buffer.append(f'{current_byte:#04x}')

    print(f"saving to {output_path} ...")

    with open(output_path, "w") as out_file:
        out_file.write(f"#define bitmap_width {img_width}\n")
        out_file.write(f"#define bitmap_height {img_height}\n")

        out_file.write("\n")

        out_file.write(
            f"static unsigned char bitmap_bits[] = {{ {", ".join(output_buffer)} }};")

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
