#include <kernel/common.h>

struct VBE_info {
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    #define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED  0
    #define MULTIBOOT_FRAMEBUFFER_TYPE_RGB      1
    #define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT 2
    uint8_t framebuffer_type;
    union
    {
        struct
        {
        uint32_t framebuffer_palette_addr;
        uint16_t framebuffer_palette_num_colors;
        };
        struct
        {
        uint8_t framebuffer_red_field_position;
        uint8_t framebuffer_red_mask_size;
        uint8_t framebuffer_green_field_position;
        uint8_t framebuffer_green_mask_size;
        uint8_t framebuffer_blue_field_position;
        uint8_t framebuffer_blue_mask_size;
        };
    };
};



void plotPixel(int x, int y, uint64_t framebuffer_addr, uint32_t framebuffer_pitch, uint32_t framebuffer_width, uint8_t r, uint8_t g, uint8_t b) {
	unsigned char *pixel = y*framebuffer_pitch + (x*4) + framebuffer_addr;
	//Red
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
	pixel[3] = 0x00;
}

