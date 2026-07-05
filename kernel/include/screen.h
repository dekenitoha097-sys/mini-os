#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

void put_char(char c);
void printk(const char *str);
void print_int(int n);
void print_hex(uint32_t n);
void clear_screen();


#endif