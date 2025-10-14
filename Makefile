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

.PHONY: all clean

all: nullos.iso test

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/i686-boot-boot.o: arch/i686/boot/boot.asm | $(BUILDDIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/libc-string.o: libc/src/string.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

$(BUILDDIR)/video-tty.o: arch/i686/video/tty.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

$(BUILDDIR)/kernel-main.o: kernel/main.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(LIBC_INCLUDEDIR) -c $< -o $@

$(BUILDDIR)/kernel.elf: $(BUILDDIR)/i686-boot-boot.o $(BUILDDIR)/kernel-main.o $(BUILDDIR)/video-tty.o $(BUILDDIR)/libc-string.o
	$(LD) $(LDFLAGS) $^ -o $@

nullos.iso: $(BUILDDIR)/kernel.elf
	cp $(BUILDDIR)/kernel.elf iso/boot/
	grub2-mkrescue -o $@ iso

clean:
	rm -rf $(BUILDDIR)

test:
	qemu-system-i386 -cdrom nullos.iso
