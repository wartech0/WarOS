#ifndef __PAGING_H
#define __PAGING_H
#include <kernel/common.h>

struct page_directory_entry {
    union {
        uint32_t entry;
        struct {
            uint32_t present :1;
            uint32_t writable :1;
            uint32_t user_page :1;
            uint32_t write_through :1;
            uint32_t cache_disabled :1;
            uint32_t accessed :1;
            uint32_t zero :1;
            uint32_t page_size :1;
            uint32_t ignored :1;
            uint32_t reserved :3;
            uint32_t addr :20;
        };
    };
};

struct page_table_entry {
    union {
        uint32_t entry;
        struct {
            uint32_t present :1;
            uint32_t writable :1;
            uint32_t user_page :1;
            uint32_t write_through :1;
            uint32_t cache_disabled :1;
            uint32_t accessed :1;
            uint32_t dirty :1;
            uint32_t zero :1;
            uint32_t global :1;
            uint32_t reserved :3;
            uint32_t addr :20;
        };
    };
};

struct page_directory {
    struct page_directory_entry entries[1024];
};

struct page_table {
    struct page_table_entry entries[1024];
};


#endif