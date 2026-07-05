#include "kbd.h"
#include "screen.h"
#include "io.h"

char cmd[CMD_SIZE];
int cmd_pos = 0;

static char keyboard_map[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=',
    '\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',
    0,'*',
    0,
    ' '
};

uint8_t read_key(void)
{
    while (!(inb(0x64) & 1));

    return inb(0x60);
}

void print_key(void)
{
    uint8_t sc = read_key();

    if (sc >= 128)
        return;

    char c = keyboard_map[sc];

    if (!c)
        return;

    if (c == '\n')
    {
        cmd[cmd_pos] = '\0';

        printk("\nCommande recue : ");
        printk(cmd);

        cmd_pos = 0;
        cmd[0] = '\0';

        printk("\nshell> ");
        return;
    }

    if (c == '\b')
    {
        if (cmd_pos > 0)
        {
            cmd_pos--;
            cmd[cmd_pos] = '\0';

            put_char('\b');
        }

        return;
    }

    if (cmd_pos < CMD_SIZE - 1)
    {
        put_char(c);

        cmd[cmd_pos++] = c;
        cmd[cmd_pos] = '\0';
    }
}