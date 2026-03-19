// screen.h
#ifndef SCREEN_H
#define SCREEN_H


#define VIDEO 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define COLOR 0x01

extern int cursor_pos;

void print(const char *str);
void print_char(char c);
void clear();

#endif