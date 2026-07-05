#include <stdint.h>
#include "screen.h"
#include "memory.h"
#include "io.h"
#include "kbd.h"


void kernel_main()
{
    printk("Bienvenue dans mon OS v1.0\n");
    printk("shell> ");

    int *ptr = (int *)kmalloc(sizeof(int));
    
    while (1)
    {
        print_key();
    }
}