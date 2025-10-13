all: build

.PHONY: build 

build:
	nasm -f elf64 sysroot/boot/boot.asm -o build/boot.o
	clang --target=x86_64-elf -ffreestanding -fno-pic -mno-red-zone -O2 -c sysroot/kernel/kernel.c -o build/kernel.o
	clang --target=x86_64-elf -ffreestanding -fno-pic -mno-red-zone -O2 build/boot.o build/kernel.o -T linker.ld -nostdlib -o build/kernel.elf -fuse-ld=lld
	cp build/kernel.elf iso/boot/
	grub-mkrescue -o nullos.iso iso/

test: build
	qemu-system-x86_64 ./nullos.iso
