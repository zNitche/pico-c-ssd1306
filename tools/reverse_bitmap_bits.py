import argparse
import re


def main(args: argparse.Namespace):
    xbm_path = args.xbm

    output_hex_list = []

    with open(xbm_path, "r") as file:
        file_data = file.read().strip().replace(" ", "").replace("\n", "")
        hex_data = re.findall(r"{(.*?)};", file_data)

        if len(hex_data) != 1:
            raise Exception(
                f"wrong hex data length, got {len(hex_data)} expected 1")

        values = hex_data[0].split(",")

        for v in values:
            bin_string = f"{int(v, 16):08b}"[::-1]
            hex_string = f"{int(bin_string, 2):#04x}"

            output_hex_list.append(hex_string)

        print(f"{{{','.join(output_hex_list)}}};")


def get_args():
    argument_parser = argparse.ArgumentParser()

    argument_parser.add_argument(
        "--xbm", type=str, help="path to .xbm file containing bitmap", required=True)

    return argument_parser.parse_args()


if __name__ == "__main__":
    main(get_args())
