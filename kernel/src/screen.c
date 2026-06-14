#include "screen.h"
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t *)0XB8000)

static int cursor_x = 0;
static int cursor_y = 0;

static uint8_t color = 0x07;

void put_char(char c){
    int pos = cursor_y * VGA_WIDTH + cursor_x;
    VGA_MEMORY[pos] = ((uint16_t)color << 8) | (uint8_t) c;
    cursor_x ++;
}