import os
import argparse
from datetime import datetime


MAX_IMG_WIDTH = 128
MAX_IMG_HEIGHT = 64

BITS_PER_BYTE = 8


def get_args():
    argument_parser = argparse.ArgumentParser()

    argument_parser.add_argument(
        "--input", type=str, help="path to image file", required=True)
    argument_parser.add_argument(
        "--output", type=str, help="path to output bitmap", required=True)
    argument_parser.add_argument("--to-h", action=argparse.BooleanOptionalAction,
                                 default=False, help="save bitmap to *.h file", required=False)

    return argument_parser.parse_args()


def dump_to_file(img_width: int, img_height: int, output_buffer: list[str], output_path: str, dump_to_h: bool):
    output_filename = str(datetime.timestamp(datetime.now()))
    output_extension = ".h" if dump_to_h else ".bitmap"

    output_file_path = os.path.join(
        output_path, f"{output_filename}{output_extension}")

    buff_struct = ', '.join(output_buffer)

    with open(output_file_path, "w") as out_file:
        out_file.write(f"#define bitmap_width {img_width}\n")
        out_file.write(f"#define bitmap_height {img_height}\n")

        out_file.write("\n")

        if dump_to_h:
            out_file.write(
                f"static uint8_t bitmap[] = {{{buff_struct}}};")

        else:
            out_file.write(
                f"static unsigned char bitmap_bits[] = {{{buff_struct}}};")
