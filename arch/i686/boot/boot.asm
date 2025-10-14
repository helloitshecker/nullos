; Multiboot2 header
section .multiboot
align 8
multiboot_header_start:
    dd 0xE85250D6                ; magic number
    dd 0                         ; architecture (0 = i386)
    dd multiboot_header_end - multiboot_header_start  ; header length
    dd -(0xE85250D6 + 0 + (multiboot_header_end - multiboot_header_start)) ; checksum

    ; End tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
multiboot_header_end:

; Stack
section .bss
align 16
stack_bottom:
    resb 16384  ; 16 KiB
stack_top:

; Kernel Entry
section .text
global _start
extern kernel_main

_start:
    ; Set up stack
    mov esp, stack_top

    ; Push multiboot info (multiboot2 passes info in ebx, magic in eax)
    push ebx
    push eax

    ; Call kernel main
    call kernel_main

    ; If kernel_main returns, hang
    cli
.hang:
    hlt
    jmp .hang
