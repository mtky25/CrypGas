#include "crypgas.h"
#include "cesar.h"
#include "aes.h"
#include "blowfish.h"
#include <stdlib.h>
#include <string.h>

void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, uint32_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César é inplace
            memcpy(output, input, len);
            break;

        case ALG_AES: {
            // // Chave igual ao main
            // unsigned char key[16] = {'k','k','k','k','e','e','e','e','y','y','y','y','.','.','.','.'};
            // enum keySize size = SIZE_16;
            // aes_cbc_result_t result = aes_encrypt_buffer_cbc(input, len, key, size);
            // if (result.ciphertext) {
            //     // copia o que couber
            //     uint32_t copy_len = (result.ciphertext_len < len) ? result.ciphertext_len : len;
            //     memcpy(output, result.ciphertext, copy_len);
            //     free(result.ciphertext);
            // }
            // break;
        }

        case ALG_BLOWFISH: {
            blowfish_ctx_t ctx;
            uint8_t key[] = {'b','l','o','w','f','i','s','h','k','e','y'};
            uint8_t iv[BLOWFISH_BLOCK_SIZE] = {0};
            uint32_t out_len = 0;

            blowfish_init(&ctx, key, sizeof(key));
            blowfish_encrypt_cbc_padded(&ctx, input, len, output, &out_len, iv);

            // Atualiza len com tamanho real
            len = out_len;
            break;
        }

        default:
            break;
    }
}

void decrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, uint32_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra_dec((char*)input, 3); 
            memcpy(output, input, len);
            break;

        case ALG_AES: {
            // // Chave igual à usada na criptografia
            // unsigned char key[16] = {'k','k','k','k','e','e','e','e','y','y','y','y','.','.','.','.'};
            // enum keySize size = SIZE_16;
            // aes_cbc_result_t result = aes_decrypt_buffer_cbc(input, len, key, size);
            // if (result.ciphertext) {
            //     uint32_t copy_len = (result.ciphertext_len < len) ? result.ciphertext_len : len;
            //     memcpy(output, result.ciphertext, copy_len);
            //     free(result.ciphertext);
            // }
            // break;
        }

        case ALG_BLOWFISH: {
            blowfish_ctx_t ctx;
            uint8_t key[] = {'b','l','o','w','f','i','s','h','k','e','y'};
            uint8_t iv[BLOWFISH_BLOCK_SIZE] = {0};
            uint32_t out_len = 0;

            blowfish_init(&ctx, key, sizeof(key));
            blowfish_decrypt_cbc_padded(&ctx, input, len, output, &out_len, iv);
            break;
        }

        default:
            break;
    }
}
