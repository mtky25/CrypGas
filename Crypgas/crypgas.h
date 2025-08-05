#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>
#include <stdint.h>

// Enum para selecionar algoritmo
typedef enum {
    ALG_CESAR = 1,
    ALG_AES = 2,
    ALG_DES = 3,
    ALG_BLOWFISH = 4
} crypto_algorithm_t;

// Função genérica para criptografar
void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, uint32_t len);

#endif
