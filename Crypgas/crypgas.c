#include "crypgas.h"
#include "cesar.h"
#include "aes.h"
#include "des.h"
#include "blowfish.h"

void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, size_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César usa inplace
            for (size_t i = 0; i < len; i++) output[i] = input[i];
            break;

        case ALG_AES:
            aes_encrypt(input, output, unsigned char *key, enum keySize size);

            break;

        case ALG_DES:
            des_encrypt(input, output, len);
            break;

        case ALG_BLOWFISH:
            size_t len = strlen(frase);
            if (frase[len - 1] == '\n') frase[len - 1] = '\0';
            len = strlen(frase);
            blowfish_encrypt_cbc(uint8_t *data, size_t len)
            break;

        default:
            // Algoritmo inválido
            break;
    }
}
