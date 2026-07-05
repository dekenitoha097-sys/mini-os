#include "memory.h"
#include <stdint.h>
#include <stddef.h>

uint32_t heap_end = HEAP_START;

void *kmalloc(size_t size)
{
    if (heap_end & 0x3)
        heap_end = (heap_end + 3) & ~3;
    
    void *ptr = (void *)heap_end;
    heap_end += size;
    return ptr;
}