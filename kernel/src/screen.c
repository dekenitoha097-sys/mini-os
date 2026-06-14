#include "screen.h"
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t *)0XB8000)

static int cursor_x = 0;
static int cursor_y = 0;

static uint8_t color = 0x07;

void put_char(char c)
{
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
        return;
    }
    int pos = cursor_y * VGA_WIDTH + cursor_x;
    VGA_MEMORY[pos] = ((uint16_t)color << 8) | (uint8_t)c;
    cursor_x++;

    if (cursor_x >= VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }

    if(cursor_y >= VGA_HEIGHT){
        cursor_y = 0;
    }
}

void printk(const char *str)
{
    while (*str)
    {
        put_char(*str);
        str++;
    }
}

void clear_screen()
{
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            int pos = y * VGA_WIDTH + x;
            VGA_MEMORY[pos] = ((uint16_t)color << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}