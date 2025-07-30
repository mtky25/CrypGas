#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>
#include <stdint.h>

// Enum para selecionar algoritmo
typedef enum {
    ALG_CESAR = 1,
    ALG_AES,
    ALG_DES,
    ALG_BLOWFISH
} crypto_algorithm_t;

// Função genérica para criptografar
void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, size_t len);

#endif
