AS := nasm
CC := i686-elf-gcc
LD := i686-elf-ld
OBJCOPY := i686-elf-objcopy

ASFLAGS := -f elf32
CFLAGS := -ffreestanding -fno-pic -m32 -Wall -Wextra -O2 -nostdlib -lgcc
LDFLAGS := -m elf_i386 -T linker.ld

INCLUDEDIR := include
LIBC_INCLUDEDIR := libc/include
BUILDDIR := build
DEPDIR := $(BUILDDIR)/.deps

# Automatically find all source files
C_SOURCES := $(wildcard kernel/*.c) \
             $(wildcard arch/i686/video/*.c) \
             $(wildcard libc/src/*.c)

ASM_SOURCES := $(wildcard arch/i686/boot/*.asm)

# Generate object file names from sources
C_OBJECTS := $(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(C_SOURCES)))
ASM_OBJECTS := $(patsubst %.asm,$(BUILDDIR)/%.o,$(notdir $(ASM_SOURCES)))

ALL_OBJECTS := $(ASM_OBJECTS) $(C_OBJECTS)

# Automatic dependency generation flags
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: all clean test

all: nullos.iso test

# Create build and dependency directories
$(BUILDDIR) $(DEPDIR):
	mkdir -p $@

# Pattern rule for C files with automatic dependency generation
$(BUILDDIR)/%.o: kernel/%.c | $(BUILDDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

$(BUILDDIR)/%.o: arch/i686/video/%.c | $(BUILDDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

$(BUILDDIR)/%.o: libc/src/%.c | $(BUILDDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

# Pattern rule for assembly files
$(BUILDDIR)/%.o: arch/i686/boot/%.asm | $(BUILDDIR)
	$(AS) $(ASFLAGS) $< -o $@

# Link all objects into kernel.elf
$(BUILDDIR)/kernel.elf: $(ALL_OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

# Create ISO image
nullos.iso: $(BUILDDIR)/kernel.elf
	cp $(BUILDDIR)/kernel.elf iso/boot/
	grub2-mkrescue -o $@ iso

clean:
	rm -rf $(BUILDDIR) nullos.iso

test:
	qemu-system-i386 -cdrom nullos.iso

# Include automatically generated dependencies
-include $(wildcard $(DEPDIR)/*.d)
