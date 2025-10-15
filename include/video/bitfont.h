#ifndef VIDEO_BITFONT_H
#define VIDEO_BITFONT_H

#include <stdint.h>

#define BITFONT_WIDTH 8
#define BITFONT_HEIGHT 8

// Use 8 as height
void bitfont_getchar(char ch, u8* word);

#endif
