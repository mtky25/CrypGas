#include "cesar.h"
#include <ctype.h>  // para isalpha, isdigit

char cifra_cesar(char c, int chave) {
    chave %= 26; 
    if (chave < 0) chave += 26;

    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + chave) % 26) + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + chave) % 26) + 'a';
    } else if (c >= '0' && c <= '9') {
        // Para números, usa módulo 10
        int chaveNum = (chave % 10 + 10) % 10;
        return ((c - '0' + chaveNum) % 10) + '0';
    }
    return c; 
}

void apply_cifra(char *str, int chave) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = cifra_cesar(str[i], chave);
    }
}

void apply_cifra_dec(char *str, int chave) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = cifra_cesar(str[i], -chave);
    }
}