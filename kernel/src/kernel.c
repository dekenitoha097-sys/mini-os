#include <stdint.h>
#include "screen.h"

void kernel_main()
{
    printk("Bienvenue dans mon OS v1.0\n");
    
    while (1)
    {
        __asm__ volatile ("hlt");
    }
}