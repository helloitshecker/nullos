#include <stdint.h>

#include <video/tty.h>

void kernel_main(uint32_t magic, uint32_t addr) {
    if (magic != 0x36d76289) {
        while(1) {
            asm volatile("hlt");
        }
    }

    tty_init();
    tty_writestring("Hello, World!\nNigga, This Works........!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

    // Hang forever
    while(1) {
        asm volatile("hlt");
    }
}
