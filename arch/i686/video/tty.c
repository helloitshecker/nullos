#include <video/tty.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_PTR 0xB8000

static uint32_t x;
static uint32_t y;
static uint8_t clearcolor;
static volatile char* ptr;

void tty_init() {
    x = 0;
    y = 0;
    clearcolor = 0xF0;
    ptr = (volatile char*)VGA_PTR;

    for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        ptr[i*2] = ' ';
        ptr[i*2+1] = clearcolor;
    }
}

void tty_putchar(char ch) {
    if (x+1 >= VGA_WIDTH) {
        x = 0;
    }

    ptr[(y * VGA_WIDTH + x) * 2] = ch;
    ptr[(y * VGA_WIDTH + x) * 2 + 1] = clearcolor;

    x++;
}

void tty_write(const char* fmt, uint32_t length) {

}

void tty_writestring(const char* fmt) {

}
