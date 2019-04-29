#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/vesa.h>
#include <kernel/paging.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(struct multiboot_info *mboot, uint32_t mboot_magic) {

	if (mboot_magic != 0x2BADB002) {
		//PANIC
		return;
	}
	terminal_initialize();
	init_descriptor_tables();
	init_interrupts();
	isrs_install();
	
	printf("flags: %s\n", itoa(mboot->flags, 2));
	printf("mem_lower: %s\n", itoa(mboot->mem_lower, 10));
	printf("mem_upper: %s\n", itoa(mboot->mem_upper, 10));
	printf("mmap length: %s\n", itoa(mboot->mmap_length, 10));
	printf("mmap addr: %s\n", itoa(mboot->mmap_addr, 16));
	printf("Bootloader: %s\n", (const char*) mboot->boot_loader_name);
	terminal_move_cursor(3);
	asm volatile("int $0x3");
    asm volatile("int $0x4");
}