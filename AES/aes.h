#ifndef AES_H
#define AES_H

#include <stddef.h>
#include <stdint.h>

enum keySize
{
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

// Função utilitária para CBC com padding e IV igual ao main
typedef struct {
    unsigned char *ciphertext;
    size_t ciphertext_len;
    unsigned char iv[16];
} aes_cbc_result_t;

aes_cbc_result_t aes_encrypt_buffer_cbc(const unsigned char *input, size_t input_len, const unsigned char *key, enum keySize size);

#endif
