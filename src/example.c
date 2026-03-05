#include <stdio.h>

#include "pico/stdlib.h"

int main() {
    stdio_init_all();

#ifdef DEBUG
    // waiting for input
    getchar();
#endif

    printf("Hello World\n");
}
