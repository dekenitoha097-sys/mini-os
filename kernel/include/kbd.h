// kbd.h
#ifndef KBD_H
#define KBD_H

extern const char kbd_US[128];

void kbd_init();
char kbd_getchar();

#endif