[BITS 32]
;Declare constants for the multiboot header.
ALI equ 1<<0                       ;align loaded modules on page boundaries
MEMINFO equ  1<<1                       ;provide memory map
VIDINFO equ 1<<2                       ;provide video info
FLAGS equ ALI | MEMINFO | VIDINFO  ;this is the Multiboot 'flag' field
MAGIC equ 0x1BADB002                 ;'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)           ;checksum of above, to prove we are multiboot

;Declare a header as in the Multiboot Standard.
section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM
dd 0, 0, 0, 0, 0
dd 1 ; 0 = set graphics mode
dd 1024, 768, 32 ; Width, height, depth

KERNEL_STACK_SIZE equ 4096

;Allocate the initial stack.
section .bootstrap_stack
align 4
stack_bottom:
resb KERNEL_STACK_SIZE
stack_top:

;The kernel entry point.
section .text
global _start
_start:
	mov esp, stack_top

	;magic number and multiboot_info pointer and address to page directory
	;kernel_main()
	push eax
	push ebx

	;Call the global constructors
	extern _init
	call _init

	;Transfer control to the main kernel.
	extern kernel_main
	call kernel_main

	;Hang if kernel_main unexpectedly returns.
	cli
hang:	
	hlt
	jmp hang