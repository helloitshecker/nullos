#include <multiboot2.h>
#include <stddef.h>


struct multiboot2_tag_framebuffer* multiboot2_get_framebuffer(uint32_t addr) {
    struct multiboot2_tag* tag;

    for (tag = (struct multiboot2_tag*)(addr + 8);
         tag->type != MULTIBOOT2_TAG_TYPE_END;
         tag = (struct multiboot2_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7))) {

        if (tag->type == MULTIBOOT2_TAG_TYPE_FRAMEBUFFER) {
            return (struct multiboot2_tag_framebuffer*)tag;
        }
    }

    return nullptr;
}
