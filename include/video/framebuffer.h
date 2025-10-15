#ifndef VIDEO_FRAMEBUFFER_H
#define VIDEO_FRAMEBUFFER_H

#include <stdint.h>

struct framebuffer {
    u32* addr;
    u32 width;
    u32 height;
    u32 pitch;
    u8 bpp;
};

void fb_init(u32 multiboot_addr);
void fb_putpixel(u32 x, u32 y, u32 color);
void fb_draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
void fb_clear(u32 color);

struct framebuffer* fb_get_info(void);

#endif
