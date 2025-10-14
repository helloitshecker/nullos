#include <stdint.h>

#include <video/tty.h>

// Simple kernel main function
void kernel_main(uint32_t magic, uint32_t addr) {
    // Verify we were booted by a Multiboot2-compliant bootloader
    if (magic != 0x36d76289) {
        // Invalid magic number - hang
        while(1) {
            asm volatile("hlt");
        }
    }

    tty_init();
    tty_putchar('H');
    tty_putchar('e');
    tty_putchar('l');
    tty_putchar('l');
    tty_putchar('o');
    tty_putchar('!');

    // Hang forever
    while(1) {
        asm volatile("hlt");
    }
}
