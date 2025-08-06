#include "blowfish.h"
#include "blowfish_tables.h"
#include <string.h>

/* Função F */
static inline uint32_t F(blowfish_ctx_t *ctx, uint32_t x) {
    uint8_t a = (x >> 24) & 0xFF;
    uint8_t b = (x >> 16) & 0xFF;
    uint8_t c = (x >> 8)  & 0xFF;
    uint8_t d = x & 0xFF;
    return ((ctx->S[0][a] + ctx->S[1][b]) ^ ctx->S[2][c]) + ctx->S[3][d];
}

void blowfish_init(blowfish_ctx_t *ctx, const uint8_t *key, uint32_t key_len) {
    memcpy(ctx->P, P_init, sizeof(P_init));
    memcpy(ctx->S, S_init, sizeof(S_init));

    uint32_t key_index = 0;
    for (int i = 0; i < 18; i++) {
        uint32_t data = 0;
        for (int k = 0; k < 4; k++) {
            data = (data << 8) | key[key_index];
            key_index = (key_index + 1) % key_len;
        }
        ctx->P[i] ^= data;
    }

    uint32_t left = 0, right = 0;
    for (int i = 0; i < 18; i += 2) {
        blowfish_encrypt_block(ctx, &left, &right);
        ctx->P[i] = left;
        ctx->P[i + 1] = right;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j += 2) {
            blowfish_encrypt_block(ctx, &left, &right);
            ctx->S[i][j] = left;
            ctx->S[i][j + 1] = right;
        }
    }
}

void blowfish_encrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right) {
    uint32_t L = *left;
    uint32_t R = *right;
    for (int i = 0; i < 16; i++) {
        L ^= ctx->P[i];
        R ^= F(ctx, L);
        uint32_t temp = L; L = R; R = temp;
    }
    uint32_t temp = L; L = R; R = temp;
    R ^= ctx->P[16];
    L ^= ctx->P[17];
    *left = L;
    *right = R;
}

void blowfish_decrypt_block(blowfish_ctx_t *ctx, uint32_t *left, uint32_t *right) {
    uint32_t L = *left;
    uint32_t R = *right;
    for (int i = 17; i > 1; i--) {
        L ^= ctx->P[i];
        R ^= F(ctx, L);
        uint32_t temp = L; L = R; R = temp;
    }
    uint32_t temp = L; L = R; R = temp;
    R ^= ctx->P[1];
    L ^= ctx->P[0];
    *left = L;
    *right = R;
}

/* PKCS#7 padding helper */
static uint32_t apply_pkcs7(uint8_t *buffer, uint32_t len) {
    uint8_t pad = BLOWFISH_BLOCK_SIZE - (len % BLOWFISH_BLOCK_SIZE);
    if (pad == 0) pad = BLOWFISH_BLOCK_SIZE; // adiciona bloco extra
    for (uint8_t i = 0; i < pad; i++)
        buffer[len + i] = pad;
    return len + pad;
}

/* CBC com padding seguro (processa bloco a bloco) */
void blowfish_encrypt_cbc_padded(blowfish_ctx_t *ctx,
                                 const uint8_t *input,
                                 uint32_t input_len,
                                 uint8_t *output,
                                 uint32_t *output_len,
                                 const uint8_t iv[BLOWFISH_BLOCK_SIZE]) {
    // calcula tamanho final com padding
    uint8_t temp[256]; // suporta até 256 bytes (pode aumentar se precisar)
    if (input_len > 248) input_len = 248; // garante espaço para padding

    memcpy(temp, input, input_len);
    uint32_t padded_len = apply_pkcs7(temp, input_len);

    uint8_t prev[8];
    memcpy(prev, iv, 8);

    // processa cada bloco de 8 bytes
    for (uint32_t i = 0; i < padded_len; i += 8) {
        uint8_t block[8];
        memcpy(block, temp + i, 8);

        // XOR com bloco anterior ou IV
        for (int j = 0; j < 8; j++)
            block[j] ^= prev[j];

        uint32_t L = (block[0]<<24)|(block[1]<<16)|(block[2]<<8)|block[3];
        uint32_t R = (block[4]<<24)|(block[5]<<16)|(block[6]<<8)|block[7];

        blowfish_encrypt_block(ctx, &L, &R);

        output[i+0] = (L >> 24) & 0xFF;
        output[i+1] = (L >> 16) & 0xFF;
        output[i+2] = (L >> 8)  & 0xFF;
        output[i+3] = L & 0xFF;
        output[i+4] = (R >> 24) & 0xFF;
        output[i+5] = (R >> 16) & 0xFF;
        output[i+6] = (R >> 8)  & 0xFF;
        output[i+7] = R & 0xFF;

        memcpy(prev, output + i, 8);
    }

    *output_len = padded_len;
}

void blowfish_decrypt_cbc_padded(blowfish_ctx_t *ctx,
                                  const uint8_t *input,
                                  uint32_t input_len,
                                  uint8_t *output,
                                  uint32_t *output_len,
                                  const uint8_t iv[BLOWFISH_BLOCK_SIZE]) {
    if (input_len % 8 != 0 || input_len == 0) {
        *output_len = 0;
        return; // inválido
    }

    uint8_t prev[8];
    memcpy(prev, iv, 8);

    for (uint32_t i = 0; i < input_len; i += 8) {
        // Lê bloco criptografado
        uint32_t L = (input[i+0]<<24)|(input[i+1]<<16)|(input[i+2]<<8)|input[i+3];
        uint32_t R = (input[i+4]<<24)|(input[i+5]<<16)|(input[i+6]<<8)|input[i+7];

        // Salva bloco atual para usar como "prev" no próximo passo
        uint8_t current_block[8];
        memcpy(current_block, input + i, 8);

        // Descriptografa bloco
        blowfish_decrypt_block(ctx, &L, &R);

        uint8_t decrypted[8];
        decrypted[0] = (L >> 24) & 0xFF;
        decrypted[1] = (L >> 16) & 0xFF;
        decrypted[2] = (L >> 8)  & 0xFF;
        decrypted[3] = L & 0xFF;
        decrypted[4] = (R >> 24) & 0xFF;
        decrypted[5] = (R >> 16) & 0xFF;
        decrypted[6] = (R >> 8)  & 0xFF;
        decrypted[7] = R & 0xFF;

        // XOR com IV ou bloco anterior
        for (int j = 0; j < 8; j++)
            decrypted[j] ^= prev[j];

        memcpy(output + i, decrypted, 8);

        memcpy(prev, current_block, 8); // atualiza prev
    }

    // Remover padding PKCS#7
    uint8_t pad = output[input_len - 1];
    if (pad == 0 || pad > 8) {
        *output_len = 0; // padding inválido
        return;
    }

    // Verifica se todos os bytes de padding são iguais
    for (int i = 1; i <= pad; i++) {
        if (output[input_len - i] != pad) {
            *output_len = 0; // padding inválido
            return;
        }
    }

    *output_len = input_len - pad;
}
