#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <stdint.h>

#define BLOWFISH_BLOCK_SIZE 8

typedef struct {
    uint32_t P[18];
    uint32_t S[4][256];
} blowfish_ctx_t;

void blowfish_init(blowfish_ctx_t *ctx, const uint8_t *key, uint32_t key_len);
void blowfish_encrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right);
void blowfish_decrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right);

/**
 * Encriptação CBC com padding PKCS#7
 */
void blowfish_encrypt_cbc_padded(blowfish_ctx_t *ctx,
                                 const uint8_t *input,
                                 uint32_t input_len,
                                 uint8_t *output,
                                 uint32_t *output_len,
                                 const uint8_t iv[BLOWFISH_BLOCK_SIZE]);

#endif
