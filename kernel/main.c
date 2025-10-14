#include <stdint.h>

// Simple kernel main function
void kernel_main(uint32_t magic, uint32_t addr) {
    // Verify we were booted by a Multiboot2-compliant bootloader
    if (magic != 0x36d76289) {
        // Invalid magic number - hang
        while(1) {
            asm volatile("hlt");
        }
    }

    // Kernel successfully booted!
    // You can add your VGA driver calls here later

    // Hang forever
    while(1) {
        asm volatile("hlt");
    }
}
