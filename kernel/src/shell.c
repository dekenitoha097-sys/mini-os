#include <shell.h>
#include <time_date.h>
#include <screen.h>


//volatile int cursor_pos = 0;  // position actuelle sur l'écran
char cmd_buffer[256]; // Le tableau qui va stocker la commande tapée
int cmd_index = 0;    // La position actuelle dans le tableau

void handle_key(char lettre) {
    if (lettre == '\n') {
        print_char('\n');    // passer à la ligne
        cmd_manager();       // exécuter la commande
        print("myshell> ");  // réafficher le prompt
    } 
    else if (lettre == '\b') {
        if (cmd_index > 0) {   // vérifier qu'il y a quelque chose à effacer
            cmd_index--;        // retirer la lettre du buffer
            print_char('\b');   // effacer à l'écran
        }
    }
    else {
        if (cmd_index < 255) {          // éviter le débordement du tableau
            cmd_buffer[cmd_index] = lettre; // sauvegarder en mémoire
            cmd_index++;                    // avancer l'index
            print_char(lettre);             // afficher à l'écran
        }
    }
}

void cmd_manager() {
    // 1. On s'assure que le mot est bien terminé
    cmd_buffer[cmd_index] = '\0';

    // 2. Si on appuie sur Entrée sans rien taper
    if (cmd_index == 0) {
        return;
    } 

    // --- NOUVEAUTÉ : SÉPARER LA COMMANDE DES ARGUMENTS ---
    char *commande = cmd_buffer; // La commande commence au début du buffer
    char *argument = "";         // Par défaut, l'argument est vide

    // On parcourt le texte tapé pour trouver le premier espace
    for (int i = 0; i < cmd_index; i++) {
        if (cmd_buffer[i] == ' ') {
            cmd_buffer[i] = '\0';          // On "coupe" le mot en mettant une fin de chaîne
            argument = &cmd_buffer[i + 1]; // L'argument commence à la case d'après
            break;                         // On arrête de chercher (on ne coupe qu'au premier espace)
        }
    }
    // -----------------------------------------------------

    // 3. À partir d'ici, on compare la variable 'commande' (et plus cmd_buffer entier)
    
    if (strcmp(commande, "cls") == 0) {
        clear();
    } 
    else if (strcmp(commande, "help") == 0) {
        print("Commandes disponibles : help, cls, echo\n");
    } 
    else if(strcmp(commande, "time") == 0){
        cmd_time();
    }
    // --- NOUVELLE COMMANDE QUI UTILISE L'ARGUMENT ---
    else if (strcmp(commande, "echo") == 0) {
        if (argument[0] == '\0') {
            print("Erreur : veuillez fournir un argument (ex: echo test)\n");
        } else {
            print(argument);
            print("\n");
        }
    }
    // ------------------------------------------------
    else {
        print("Commande introuvable : ");
        print(commande);
        print("\n");
    }

    // 6. On remet l'index à 0 pour la prochaine commande
    cmd_index = 0;
}
