#include "crypgas.h"
#include "cesar.h"
#include "aes.h"
// #include "des.h"
#include "blowfish.h"

void encrypt(crypto_algorithm_t alg, uint8_t *input, uint8_t *output, size_t len) {
    switch (alg) {
        case ALG_CESAR:
            apply_cifra((char*)input, 3); // César usa inplace
            for (size_t i = 0; i < len; i++) output[i] = input[i];
            break;

        case ALG_AES: {
            // Chave igual ao main
            unsigned char key[16] = {'k','k','k','k','e','e','e','e','y','y','y','y','.','.','.','.'};
            enum keySize size = SIZE_16;
            aes_cbc_result_t result = aes_encrypt_buffer_cbc(input, len, key, size);
            if (result.ciphertext && result.ciphertext_len <= len) {
                memcpy(output, result.ciphertext, result.ciphertext_len);
            } else if (result.ciphertext) {
                // Se output for menor que ciphertext_len, copia só o que cabe
                memcpy(output, result.ciphertext, len);
            }
            // (Opcional: salvar IV em algum lugar, se precisar para descriptografia)
            if (result.ciphertext) free(result.ciphertext);
            break;
        }

        case ALG_DES:
            // des_encrypt(input, output, len);
            break;

        case ALG_BLOWFISH:
            // size_t len = strlen(input);
            // if (input[len - 1] == '\n') 
            //     input[len - 1] = '\0';
            // len = strlen(input);
            // blowfish_encrypt_cbc(uint8_t *data, size_t len);
            // break;

        default:
            break;
    }
}
