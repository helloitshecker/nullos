#include <video/tty.h>

#include <string.h>

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
    clearcolor = 0x9F;
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


void tty_putcharat(size _x, size _y, char ch) {
    if (_x+1 >= VGA_WIDTH) {
        _x = 0;
    }

    ptr[(_y * VGA_WIDTH + _x) * 2] = ch;
    ptr[(_y * VGA_WIDTH + _x) * 2 + 1] = clearcolor;
}

void tty_scroll() {
    for (size i = 0; i < VGA_HEIGHT-1; i++) {
        for (size j = 0; j < VGA_WIDTH; j++) {
            const char downchar = (char)ptr[2*((i+1)*VGA_WIDTH + j)];
            ptr[2*(i*VGA_WIDTH + j)] = downchar;
        }
    }
}

void tty_write(const char* fmt, uint32_t length) {
    for (size i = 0; i < length; i++) {
        if (fmt[i] == '\n') {
            if (y+1 >= VGA_HEIGHT) {
                x = 0;
                tty_scroll();
            } else {
                y++;
                x = 0;
            }
        } else {
            if (x+1 >= VGA_WIDTH) {
                x = 0;
                if (y+1 >= VGA_HEIGHT) {
                    y = 0;
                } else {
                    y += 1;
                }
            }

            tty_putchar(fmt[i]);
        }
    }
}

void tty_writestring(const char* fmt) {
    tty_write(fmt, strlen(fmt));
}
