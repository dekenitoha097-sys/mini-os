#ifndef KBD_H
#define KBD_H

#include <stdint.h>

#define CMD_SIZE 256

extern char cmd[CMD_SIZE];
extern int cmd_pos;

uint8_t read_key(void);
void print_key(void);

#endif