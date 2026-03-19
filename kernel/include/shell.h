// shell.h
#ifndef SHELL_H
#define SHELL_H

void cmd_manager();
void handle_key(char lettre);
extern char cmd_buffer[256];
extern int cmd_index;

#endif