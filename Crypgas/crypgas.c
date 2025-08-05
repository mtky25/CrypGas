#include "crypgas.h"
#include "cesar.h"
#include "aes.h"
#include "blowfish.h"
#include <stdlib.h>
#include <string.h>

/* Criptografar: retorna tamanho real do output */
uint32_t encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, uint32_t len) {
    uint32_t output_len = 0;

    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César é inplace
            memcpy(output, input, len);
            output_len = len;
            break;

        case ALG_AES:
            // Placeholder AES CBC (implementar se necessário)
            memcpy(output, input, len);
            output_len = len;
            break;

        case ALG_BLOWFISH: {
            blowfish_ctx_t ctx;
            uint8_t key[] = {'b','l','o','w','f','i','s','h','k','e','y'};
            uint8_t iv[BLOWFISH_BLOCK_SIZE] = {0};

            blowfish_init(&ctx, key, sizeof(key));
            blowfish_encrypt_cbc_padded(&ctx, input, len, output, &output_len, iv);
            break;
        }

        default:
            output_len = 0;
            break;
    }

    return output_len;
}

/* Descriptografar: retorna tamanho real do output */
uint32_t decrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, uint32_t len) {
    uint32_t output_len = 0;

    switch (alg) {
        case ALG_CESAR:
            apply_cifra_dec((char*)input, 3);
            memcpy(output, input, len);
            output_len = len;
            break;

        case ALG_AES:
            // Placeholder AES CBC
            memcpy(output, input, len);
            output_len = len;
            break;

        case ALG_BLOWFISH: {
            blowfish_ctx_t ctx;
            uint8_t key[] = {'b','l','o','w','f','i','s','h','k','e','y'};
            uint8_t iv[BLOWFISH_BLOCK_SIZE] = {0};

            blowfish_init(&ctx, key, sizeof(key));
            blowfish_decrypt_cbc_padded(&ctx, input, len, output, &output_len, iv);
            break;
        }

        default:
            output_len = 0;
            break;
    }

    return output_len;
}
