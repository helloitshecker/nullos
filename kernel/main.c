#include <stdint.h>
#include <stdlib.h>

#include <video/tty.h>
#include <video/framebuffer.h>
#include <video/bitfont.h>
#include <video/terminal.h>

void kernel_main(uint32_t magic, uint32_t addr) {
    if (magic != 0x36d76289) {
        while(1) {
            __asm__ volatile("hlt");
        }
    }

    terminal_init(addr, 4);
    terminal_writestring("Hello, World!");

    // Hang forever
    while(1) {
        __asm__ volatile("hlt");
    }
}
