#ifndef VIDEO_TERMINAL_H
#define VIDEO_TERMINAL_H

#include <stdint.h>

void terminal_init(u32 multiboot_addr, size _scale);
void terminal_exit();

void terminal_clear();

void terminal_putchar(u32 fg, u32 bg, char ch);

void terminal_writestring(const char* str);

#endif
