#include "multiboot2.h"
#include <video/framebuffer.h>
#include <stddef.h>

static struct framebuffer fb = {};

void fb_init(u32 multiboot_addr) {
    struct multiboot2_tag_framebuffer* fb_tag = multiboot2_get_framebuffer(multiboot_addr);

    if (fb_tag == nullptr) {
        // Framebuffer not available
        return;
    }

    fb.addr = (u32*)(u32)fb_tag->framebuffer_addr;
    fb.width = fb_tag->framebuffer_width;
    fb.height = fb_tag->framebuffer_height;
    fb.pitch = fb_tag->framebuffer_pitch;
    fb.bpp = fb_tag->framebuffer_bpp;
}

void fb_putpixel(u32 x, u32 y, u32 color) {
    if (x >= fb.width || y >= fb.height || fb.addr == nullptr) {
        return;
    }

    u32* pixel = fb.addr + (y * fb.pitch / 4) + x;
    *pixel = color;
}

void fb_draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    for (u32 dy = 0; dy < h; dy++) {
        for (u32 dx = 0; dx < w; dx++) {
            fb_putpixel(x + dx, y + dy, color);
        }
    }
}

void fb_clear(u32 color) {
    if (fb.addr == nullptr) {
        return;
    }

    for (u32 y = 0; y < fb.height; y++) {
        for (u32 x = 0; x < fb.width; x++) {
            fb_putpixel(x, y, color);
        }
    }
}

struct framebuffer* fb_get_info(void) {
    return &fb;
}
