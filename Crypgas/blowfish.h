#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <stdint.h>

#define BLOWFISH_BLOCK_SIZE 8  // Tamanho do bloco em bytes

// Definindo o tipo para o contexto do Blowfish
typedef struct {
    uint32_t P[18];    // Vetor de subchaves P
    uint32_t S[4][256];  // Tabelas S (cada uma com 256 entradas)
} blowfish_ctx_t;

// Estrutura para o resultado da criptografia (caso seja necessário no CBC)
typedef struct {
    uint8_t *ciphertext;    // Ponteiro para o texto criptografado
    uint32_t ciphertext_len; // Tamanho do texto criptografado
} crypto_cbc_result_t;  // Renomeado para ser genérico e adequado ao contexto

// Função para inicializar o contexto do Blowfish com a chave
void blowfish_init(blowfish_ctx_t *ctx, const uint8_t *key, uint32_t key_len);

// Função para criptografar um bloco com Blowfish
void blowfish_encrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right);

// Função para descriptografar um bloco com Blowfish
void blowfish_decrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right);

// Função para criptografar com Blowfish no modo CBC com padding seguro
void blowfish_encrypt_cbc_padded(blowfish_ctx_t *ctx,
                                  const uint8_t *input,
                                  uint32_t input_len,
                                  uint8_t *output,
                                  uint32_t *output_len,
                                  const uint8_t iv[BLOWFISH_BLOCK_SIZE]);

// Função para descriptografar com Blowfish no modo CBC com padding seguro
void blowfish_decrypt_cbc_padded(blowfish_ctx_t *ctx,
                                  const uint8_t *input,
                                  uint32_t input_len,
                                  uint8_t *output,
                                  uint32_t *output_len,
                                  const uint8_t iv[BLOWFISH_BLOCK_SIZE]);

#endif // BLOWFISH_H
