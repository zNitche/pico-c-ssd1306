# pico-c-ssd1306
PicoSDK (C) module for SSD1306 powered 128x64px display

#### Features
- device initialization
- turn screen on/off
- clear screen
- render bitmaps
- custom 8bit (8x8px) font
- texts rendering with characters spacing & wrapping

#### Usage
Example at [example.c](src/example.c)

#### Connect to device
```
screen /dev/tty1
```

to exit 
```
CTRL + A -> CTRL + \
```

#### Development setup (devcontainer)

1. get pico-sdk
```
mkdir -p ~/SDKs/pico-sdk
cd ~/SDKs/pico-sdk
git clone -b "2.2.0" --single-branch https://github.com/raspberrypi/pico-sdk.git 2.2.0
```

2. initialize dependencies
```
cd ~/SDKs/pico-sdk/2.2.0
git submodule update --init
```

3. open project in devcontainer
4. setup project

```
cmake -S . -B build
```

or for debug mode

```
cmake -DDEBUG=1 -S . -B build
```

5. build
```
cd build
make
```

6. enable auto copying of `.uf2` file to MCU
```
sh copy_uf2.sh ./build/example.uf2 /Volumes/RPI-RP2
```

### Tools

##### generate bitmap from image
```
python3 tools/convert_to_bitmap.py --input resources/ssd1306_test.png --output resources/test.bitmap
```

### Resources
- [Datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
- [pico-sdk ssd1306 lib](https://github.com/raspberrypi/pico-examples/tree/master/i2c/ssd1306_i2c)
