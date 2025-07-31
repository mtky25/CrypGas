#include "crypgas.h"
#include "cesar.h"
// #include "aes.h"
#include "../AES/aes.h"
// #include "des.h"
// #include "blowfish.h"

void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, size_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César usa inplace
            for (size_t i = 0; i < len; i++) output[i] = input[i];
            break;

        case ALG_AES: {
            // Chave igual ao main
            unsigned char key[16] = {'k','k','k','k','e','e','e','e','y','y','y','y','.','.','.','.'};
            enum keySize size = SIZE_16;
            aes_cbc_result_t result = aes_encrypt_buffer_cbc(input, len, key, size);
            if (result.ciphertext && result.ciphertext_len <= len) {
                memcpy(output, result.ciphertext, result.ciphertext_len);
            } else if (result.ciphertext) {
                // Se output for menor que ciphertext_len, copia só o que cabe
                memcpy(output, result.ciphertext, len);
            }
            // (Opcional: salvar IV em algum lugar, se precisar para descriptografia)
            if (result.ciphertext) free(result.ciphertext);
            break;
        }

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
