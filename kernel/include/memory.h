#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define HEAP_START 0x100000
extern uint32_t heap_end;

void *kmalloc(size_t size);

#endif