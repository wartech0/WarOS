#include <kernel/idt.h>

extern void idt_load(uint32_t);

static idt_t idt_entries[256];
static idt_ptr_t idt_p;

void init_interrupts() {
    idt_p.limit = (sizeof(idt_t)*256) - 1;
    idt_p.base = (uint32_t)&idt_entries;
    memset(&idt_entries, 0, sizeof(idt_t) * 256);

    idt_load((uint32_t)&idt_p);

    printf("IDT Initialized....\n");
}
    
void idt_set_gate(uint32_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    printf("base: %s", itoa(base, 16));
    idt_entries[num].offset_low = base & 0xFFFF;
    idt_entries[num].offset_high = (uint16_t)(base >> 16) & 0xFFFF;
    idt_entries[num].seg_selector = sel;
    idt_entries[num].zero = 0;
    idt_entries[num].type_attr = flags;
}    