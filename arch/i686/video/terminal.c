#include "multiboot2.h"
#include <video/terminal.h>

#include <string.h>

#include <video/framebuffer.h>
#include <video/bitfont.h>

static size cursor_x;
static size cursor_y;
static size screen_x;
static size screen_y;
static size scale;
static u32  word_fg;
static u32  word_bg;
static u8 font_word[8];

void terminal_init(u32 multiboot_addr, size _scale) {
    fb_init(multiboot_addr);
    fb_clear(word_bg);

    scale = _scale;

    struct framebuffer* fbin = fb_get_info();
    cursor_x = 0;
    cursor_y = 0;
    screen_x = fbin->width / (BITFONT_WIDTH * scale);
    screen_y = fbin->height / (BITFONT_HEIGHT * scale);
    word_fg = 0xFFFFFF;
    word_bg = 0x000000;
}

void terminal_exit() {

}

void terminal_clear() {
    fb_clear(word_bg);
}

void terminal_putchar(u32 fg, u32 bg, char ch) {
    if (ch == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= screen_y) {
            // TODO: scroll
            cursor_y = 0; // temp: wrap to top
        }
        return;
    }

    // Draw character
    bitfont_getchar(ch, font_word);
    for (size y = 0; y < BITFONT_HEIGHT; y++) {
        for (size x = 0; x < BITFONT_WIDTH; x++) {
            if (font_word[y] & (1 << x)) {
                fb_draw_rect((cursor_x * BITFONT_WIDTH * scale) + scale * x,
                        (cursor_y * BITFONT_HEIGHT * scale) + scale * y,
                        scale, scale, fg);
            }
        }
    }

    // Move cursor
    cursor_x++;
    if (cursor_x >= screen_x) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= screen_y) {
            // TODO: scroll
            cursor_y = 0; // temp: wrap to top
        }
    }
}

void terminal_writestring(const char* str) {
    const size len = strlen(str);

    for (size i = 0; i < len; i++) {
        terminal_putchar(word_fg, word_bg, str[i]);
    }
}
