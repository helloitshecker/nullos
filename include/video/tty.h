#ifndef VIDEO_TTY_H
#define VIDEO_TTY_H

#include <stdint.h>

void tty_init();
void tty_putchar(char ch);
void tty_putcharat(size _x, size _y, char ch);
void tty_scroll();
void tty_write(const char* fmt, uint32_t length);
void tty_writestring(const char* fmt);

#endif
