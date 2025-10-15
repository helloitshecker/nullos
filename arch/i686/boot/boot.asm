; Multiboot2 header
section .multiboot
align 8
multiboot_header_start:
    dd 0xE85250D6                ; magic number
    dd 0                         ; architecture (0 = i386)
    dd multiboot_header_end - multiboot_header_start  ; header length
    dd -(0xE85250D6 + 0 + (multiboot_header_end - multiboot_header_start)) ; checksum

    ; Framebuffer tag (optional)
    align 8
    dw 5                  ; type = framebuffer
    dw 1                  ; flags = optional
    dd 20                 ; size
    dd 1024               ; width
    dd 768                ; height
    dd 32                 ; bpp

    ; EFI boot services tag
    align 8
    dw 7                  ; type = EFI boot services
    dw 0                  ; flags
    dd 8                  ; size

    ; EFI amd64 entry address tag
    align 8
    dw 9                  ; type = EFI amd64 entry point
    dw 0                  ; flags
    dd 12                 ; size
    dd efi_entry          ; entry point address (32-bit)

    ; End tag (required)
    align 8
    dw 0                  ; type
    dw 0                  ; flags
    dd 8                  ; size
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
global efi_entry
extern kernel_main

; BIOS Entry Point (32-bit protected mode)
[BITS 32]
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

; UEFI Entry Point (64-bit long mode)
[BITS 64]
efi_entry:
    ; Disable interrupts (UEFI leaves them enabled!)
    cli

    ; Set up stack
    mov rsp, stack_top

    ; In 64-bit mode, RDI contains the MBI pointer
    ; RDI is already the first argument for kernel_main
    ; But we need to pass magic number too (in EAX)
    mov rsi, rdi          ; Move MBI to second argument
    mov edi, 0x36d76289   ; Multiboot2 magic for first argument

    ; Call kernel main
    call kernel_main

    ; If kernel_main returns, hang
    cli
.hang64:
    hlt
    jmp .hang64
