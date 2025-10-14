#include <stdint.h>
#include <stdlib.h>

#include <video/tty.h>

void kernel_main(uint32_t magic, uint32_t addr) {
    if (magic != 0x36d76289) {
        while(1) {
            asm volatile("hlt");
        }
    }

    tty_init();

    char waste[1000];
    char buf[10];
    for (int i = 0; i < 100; i++) {
        itoa(i, buf);
        tty_writestring(buf);
        tty_writestring("\n");

        for (volatile int x = 0; x < (int)(INT32_MAX/400); x++) {
            itoa(x, waste);
        }
    }


    // Hang forever
    while(1) {
        asm volatile("hlt");
    }
}
