#include "crypgas.h"
#include "cesar.h"
// #include "aes.h"
// #include "des.h"
// #include "blowfish.h"

void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, size_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César usa inplace
            for (size_t i = 0; i < len; i++) output[i] = input[i];
            break;

        case ALG_AES:
            aes_encrypt(input, output, len);
            break;

        case ALG_DES:
            des_encrypt(input, output, len);
            break;

        case ALG_BLOWFISH:
            blowfish_encrypt(input, output, len);
            break;

        default:
            // Algoritmo inválido
            break;
    }
}



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
