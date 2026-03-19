#include <stdint.h>
#include <screen.h>

int cursor_pos = 0;
// fonction pour ecrire a l'ecran
void print(const char *str) {
    volatile char *video = (char *) VIDEO;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH); // passage à la ligne
        } else {
            video[cursor_pos * 2] = str[i];
            video[cursor_pos * 2 + 1] = COLOR;
            cursor_pos++;
        }
    }
}

// --- NOUVELLE FONCTION POUR AFFICHER UN SEUL CARACTÈRE ---
void print_char(char c) {
    volatile char *video = (char *) VIDEO;
    
    if (c == '\n') {
        cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH); // passage à la ligne
        //print("myshell > ");
     }
    else if (c == '\b') {
        if (cursor_pos > 0) { // On vérifie qu'on ne sort pas de l'écran par le haut
            cursor_pos--;                     // 1. On recule
            video[cursor_pos * 2] = ' ';      // 2. On "efface" avec un espace
            video[cursor_pos * 2 + 1] = COLOR; 
        }
    } else {
        video[cursor_pos * 2] = c;
        video[cursor_pos * 2 + 1] = COLOR;
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