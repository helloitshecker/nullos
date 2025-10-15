#include "video/framebuffer.h"
#include <stdint.h>
#include <stdlib.h>

#include <video/terminal.h>

#include <img.h>

extern char kernel_end;

static inline void delay(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 10000; i++) {
        __asm__ volatile ("nop");
    }
}

void kernel_main(uint32_t magic, uint32_t addr) {
    if (magic != 0x36d76289) {
        while(1) {
            __asm__ volatile("hlt");
        }
    }

    terminal_init(addr, 6);

    // Initialize Malloc
    __malloc_init__();

    #define FW 250
    #define FH 208

    #define OX 387
    #define OY 180


    for (size x = 0; x< 13; x++)
        terminal_writestring_with_color(0x5efffc, 0xd15eff, "\n");
    terminal_writestring_with_color(0x5EFFFC, 0xD15EFF, " Welcome to Null OS!");

    for (size frame = 0; frame < UINT32_MAX; frame++) {

        for (size y = 0; y < FH; y++) {
            for (size x = 0; x < FW; x++) {
                fb_putpixel(OX+x, OY+y, img[frame%10][y][x]);
            }
        }

        delay(800);
    }



    // Hang forever
    while(1) {
        __asm__ volatile("hlt");
    }
}
