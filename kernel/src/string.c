#include "string.h"

// returne la taille d'une chaine de caractére 
int strlen(const char *str)
{
    int len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}

// comparé deux chaines de carracte
int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if(*str1 != *str2)
            continue;

        str1++;
        str2++;
    }
    return *str1 == *str2;
}


// copié une chaine de caractére dans une autre 
void strcpy(const char* src, char* dest){
    while(*src){
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
}

