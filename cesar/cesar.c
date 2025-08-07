#include <ctype.h>  // para isalpha, isdigit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_entrada.txt>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    fseek(fin, 0, SEEK_END);
    long tamanho = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    char *buffer = malloc(tamanho + 1);
    if (!buffer) {
        perror("Erro de memória");
        fclose(fin);
        return 1;
    }

    fread(buffer, 1, tamanho, fin);
    buffer[tamanho] = '\0';
    fclose(fin);

    int chave = 3;

    // Criptografa
    char *cript = strdup(buffer);
    apply_cifra(cript, chave);
    printf("Criptografado:\n%s\n", cript);

    // Decriptografa
    char *decript = strdup(cript);
    apply_cifra_dec(decript, chave);
    printf("Decriptografado:\n%s\n", decript);

    free(buffer);
    free(cript);
    free(decript);

    return 0;
}