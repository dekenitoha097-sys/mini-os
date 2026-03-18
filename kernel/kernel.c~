#include <stdint.h>
#include <io.h>

#define VIDEO 0xB8000
//#define WHITE_ON_BLACK 0x07
#define BLUE_ON_BLACK 0x01
#define SCREEN_WIDTH 80

volatile int cursor_pos = 0;  // position actuelle sur l'écran

// Tableau de traduction : Index = Scancode, Valeur = Caractère -
const char kbd_US[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,   
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*', 0, ' '
};

// fonction pour ecrire a l'ecran
void print(const char *str) {
    volatile char *video = (char *) VIDEO;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH); // passage à la ligne
        } else {
            video[cursor_pos * 2] = str[i];
            video[cursor_pos * 2 + 1] = BLUE_ON_BLACK;
            cursor_pos++;
        }
    }
}

// --- NOUVELLE FONCTION POUR AFFICHER UN SEUL CARACTÈRE ---
void print_char(char c) {
    volatile char *video = (char *) VIDEO;
    
    if (c == '\n') {
        cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH); // passage à la ligne
        print("myshell > ");
    } else {
        video[cursor_pos * 2] = c;
        video[cursor_pos * 2 + 1] = BLUE_ON_BLACK;
        cursor_pos++;
    }
}

// fonction pour effacer l'ecran
void clear() {
    char *video = (char*) 0xb8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }
    cursor_pos = 0;
}

void kernel_main() {
	
	unsigned char scancode;
    unsigned char status;
    print("myshell > ");  
 
    // 2. La boucle infinie de ton OS
    while (1) {
        // On lit le port de statut (0x64)
        status = inb(0x64);

        // Si le bit le plus à droite est à 1, ça veut dire qu'une touche est en attente
        if (status & 0x01) {
            // On lit la touche sur le port de données (0x60)
            scancode = inb(0x60);

            // Le clavier envoie un code quand on APPUIE et un autre quand on RELÂCHE.
            // Les codes de relâchement sont toujours supérieurs à 128 (0x80).
            // On ignore les relâchements pour ne pas écrire la lettre deux fois.
            if (scancode < 128) {
                // On traduit le scancode en lettre grâce à notre tableau
                char lettre = kbd_US[scancode];
                
                // Si la lettre existe (différente de 0)
                if (lettre != 0) {
                    // ICI : Appelle TA fonction pour afficher le caractère à l'écran !
                    // Exemple : terminal_putchar(lettre);
                    print_char(lettre);
                    
                }
            }
        }
    }
}
