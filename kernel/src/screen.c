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
    /* Backspace */
    if (c == '\b')
    {
        if (cursor_x > 0)
        {
            cursor_x--;

            int pos = cursor_y * VGA_WIDTH + cursor_x;
            VGA_MEMORY[pos] = ((uint16_t)color << 8) | ' ';
        }

        return;
    }

    /* Nouvelle ligne */
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;

        if (cursor_y >= VGA_HEIGHT)
            cursor_y = 0;

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

    if (cursor_y >= VGA_HEIGHT)
    {
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

void print_int(int n)
{
    char buffer[12];
    int i = 0;

    if (n == 0)
    {
        put_char('0');
        return;
    }

    while (n > 0)
    {
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    }

    while (i > 0)
    {
        put_char(buffer[--i]);
    }
}

void print_hex(uint32_t n)
{
    char hex[] = "0123456789ABCDEF";

    printk("0x");

    for (int i = 28; i >= 0; i -= 4)
    {
        put_char(hex[(n >> i) & 0xF]);
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

