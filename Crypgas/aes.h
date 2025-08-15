#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <stddef.h>

#define AES_BLOCK_SIZE 16

typedef struct {
    uint8_t round_keys[176]; // 11 round keys (16 bytes cada) para AES-128
} aes_ctx_t;
void aes_init(aes_ctx_t *ctx, const uint8_t *key);
void aes_encrypt_block(aes_ctx_t *ctx, uint8_t block[16]);
void aes_decrypt_block(aes_ctx_t *ctx, uint8_t block[16]);
void aes_encrypt_cbc_padded(aes_ctx_t *ctx, const uint8_t *input, uint32_t len,
                            uint8_t *output, uint32_t *out_len, const uint8_t iv[16]);
void aes_decrypt_cbc_padded(aes_ctx_t *ctx, const uint8_t *input, uint32_t len,
                            uint8_t *output, uint32_t *out_len, const uint8_t iv[16]);

#endif
