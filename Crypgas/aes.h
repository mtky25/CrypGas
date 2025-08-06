#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <stddef.h>

#define AES_BLOCK_SIZE 16

typedef struct {
    uint8_t round_keys[176]; // 11 round keys de 16 bytes (AES-128)
} aes_ctx_t;

/* Inicializa chave AES-128 */
void aes_init(aes_ctx_t *ctx, const uint8_t *key, size_t key_len);

/* Criptografa um bloco */
void aes_encrypt_block(aes_ctx_t *ctx, const uint8_t in[AES_BLOCK_SIZE], uint8_t out[AES_BLOCK_SIZE]);

/* Descriptografa um bloco */
void aes_decrypt_block(aes_ctx_t *ctx, const uint8_t in[AES_BLOCK_SIZE], uint8_t out[AES_BLOCK_SIZE]);

/* CBC com PKCS#7 */
void aes_encrypt_cbc_padded(aes_ctx_t *ctx, const uint8_t *input, uint32_t len,
                            uint8_t *output, uint32_t *out_len, uint8_t iv[AES_BLOCK_SIZE]);

void aes_decrypt_cbc_padded(aes_ctx_t *ctx, const uint8_t *input, uint32_t len,
                            uint8_t *output, uint32_t *out_len, uint8_t iv[AES_BLOCK_SIZE]);

#endif
