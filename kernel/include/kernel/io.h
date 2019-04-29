#ifndef __KERNEL_IO_H
#define __KERNEL_IO_H
#include <kernel/common.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif