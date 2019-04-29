#ifndef __KERNEL_INTERRUPT_H
#define __KERNEL_INTERRUPT_H
#include <kernel/common.h>

#define ISR_TYPE_ATTR 0x8E
#define TRAP_TYPE_ATTR 0x8F

struct idt_struct {
    uint16_t offset_low;
    uint16_t seg_selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));
typedef struct idt_struct idt_t;

struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

/* Registers */
struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};
typedef struct regs regs_t;

typedef void (*irq_handler_t) (struct regs *);

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void init_interrupts();
void isrs_install();
void idt_set_gate(uint32_t num, uint32_t base, uint16_t sel, uint8_t flags);
void dump_interrupt_tables();

#endif