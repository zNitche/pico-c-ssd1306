import os


FONTS_PATH = "./resources/8bit_font"
FONTS_OUTPUT_PATH = "./resources/8bit_font_bitmaps"


def main():
    for file in os.listdir(FONTS_PATH):
        file_name = file.replace(".png", "")

        file_path = os.path.join(FONTS_PATH, file)
        file_output_path = os.path.join(FONTS_OUTPUT_PATH)

        print(f"processing {file} ...")

        os.system(
            f"python3 ./tools/convert_to_bitmap.py --to-h --input '{file_path}' --output '{file_output_path}' --output-file-name '{file_name}'")

    print("done.")


if __name__ == "__main__":
    main()
