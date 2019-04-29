#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <kernel/common.h>
#include <kernel/io.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_move_cursor(unsigned short pos);

#endif
