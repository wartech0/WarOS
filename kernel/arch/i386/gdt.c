#include <kernel/gdt.h>

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

extern void gdt_flush(uint32_t);
static void init_gdt();
static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void init_descriptor_tables() {
    init_gdt();
}

void dump_descriptor_tables() {
    printf("GDT[0].base_low: %s\n", itoa(0, 16));
    printf("GDT[0].base_middle: %s\n", itoa(gdt_entries[0].base_middle, 16));
    printf("GDT[0].base_high: %s\n", itoa(gdt_entries[0].base_high, 16));
    printf("GDT[0].limit_low: %s\n", itoa(gdt_entries[0].limit_low, 16));
    printf("GDT[0].granularity: %s\n", itoa(gdt_entries[0].granularity, 16));
    printf("GDT[0].access: %s\n\n", itoa(gdt_entries[0].access, 16));

    printf("GDT[1].base_low: %s\n", itoa(gdt_entries[1].base_low, 16));
    printf("GDT[1].base_middle: %s\n", itoa(gdt_entries[1].base_middle, 16));
    printf("GDT[1].base_high: %s\n", itoa(gdt_entries[1].base_high, 16));
    printf("GDT[1].limit_low: %s\n", itoa(gdt_entries[1].limit_low, 16));
    printf("GDT[1].granularity: %s\n", itoa(gdt_entries[1].granularity, 16));
    printf("GDT[1].access: %s\n\n", itoa(gdt_entries[1].access, 16));

    printf("GDT[2].base_low: %s\n", itoa(gdt_entries[2].base_low, 16));
    printf("GDT[2].base_middle: %s\n", itoa(gdt_entries[2].base_middle, 16));
    printf("GDT[2].base_high: %s\n", itoa(gdt_entries[2].base_high, 16));
    printf("GDT[2].limit_low: %s\n", itoa(gdt_entries[2].limit_low, 16));
    printf("GDT[2].granularity: %s\n", itoa(gdt_entries[2].granularity, 16));
    printf("GDT[2].access: %s\n\n", itoa(gdt_entries[2].access, 10));
}

static void init_gdt() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0); //null
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //code
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //data
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data

    gdt_flush((uint32_t)&gdt_ptr);

    printf("GDT Initialized\n");
}

static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access      = access;
}