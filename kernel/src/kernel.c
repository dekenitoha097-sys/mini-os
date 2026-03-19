#include <stdint.h>
#include <io.h>
#include <str.h>
#include <screen.h>
#include <kbd.h>
#include <shell.h>

void kernel_main() {
    unsigned char scancode;
    unsigned char status;

    print("myshell> ");

    while (1) {
        // Vérifier si une touche est disponible
        status = inb(0x64);
        if (!(status & 0x01)) continue;

        scancode = inb(0x60);
        if (scancode >= 128) continue;   // ignorer les relâchements

        char lettre = kbd_US[scancode];
        if (lettre != 0) {
            handle_key(lettre);          // déléguer la gestion à la fonction
        }
    }
}