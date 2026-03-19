#include <str.h>

// --- FONCTION POUR COMPARER DEUX MOTS ---
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


int str_to_int(char *str){
	int res = 0;
	for(int i=0; str[i] != '\0';i++){
		if(str[i] >=0 && str[i] <= 9){
			res = res * 10 + (str[i] - '0');
		}
	}
	return res;
}

// --- OUTIL 2 : Convertir un vrai nombre en texte (ex: 42 -> "42") ---
void int_to_str(int n, char *buffer) {
    int i = 0;
    int is_neg = 0;
    
    if (n == 0) { buffer[0] = '0'; buffer[1] = '\0'; return; }
    if (n < 0)  { is_neg = 1; n = -n; } // Gestion des nombres négatifs
    
    // On extrait les chiffres un par un (à l'envers)
    while (n > 0) {
        buffer[i++] = (n % 10) + '0';
        n = n / 10;
    }
    if (is_neg) buffer[i++] = '-';
    buffer[i] = '\0';
    
    // On inverse le texte pour le mettre à l'endroit
    int start = 0, end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++; end--;
    }
}