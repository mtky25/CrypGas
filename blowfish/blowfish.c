#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define N 16

// Tabela P e S-boxes (valores iniciais, simplificados)
uint32_t P[18] = {
    0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344,
    0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89,
    0x452821E6, 0x38D01377, 0xBE5466CF, 0x34E90C6C,
    0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917,
    0x9216D5D9, 0x8979FB1B
};

uint32_t S[4][256] = {
    {0xD1310BA6, 0x98DFB5AC, 0x2FFD72DB, 0xD01ADFB7, 0xB8E1AFED, 0x6A267E96, 0xBA7C9045, 0xF12C7F99},
    {0x4B7A70E9, 0xB5B32944, 0xDB75092E, 0xC4192623, 0xAD6EA6B0, 0x49A7DF7D, 0x9CEE60B8, 0x8FEDB266},
    {0x78AF2FDA, 0x55605C60, 0xE65525F3, 0xAA55AB94, 0x57489862, 0x63E81440, 0x55CA396A, 0x2AAB10B6},
    {0x6B8FE4D6, 0x99F73FD6, 0xA1D29C07, 0xEFE830F5, 0x4D2D38E6, 0xF0255DC1, 0x4CDD2086, 0x8470EB26}
    // ... complete as S-boxes para uso real ...
};

uint32_t F(uint32_t x) {
    // Exemplo simplificado: ideal seria usar S-boxes reais
    return ((x >> 24) ^ (x >> 16) ^ (x >> 8) ^ x);
}

void blowfish_encrypt(uint32_t *left, uint32_t *right) {
    int i;
    uint32_t L = *left;
    uint32_t R = *right;

    for (i = 0; i < N; i++) {
        L ^= P[i];
        R ^= F(L);
        uint32_t temp = L;
        L = R;
        R = temp;
    }
    uint32_t temp = L;
    L = R;
    R = temp;

    R ^= P[N];
    L ^= P[N + 1];

    *left = L;
    *right = R;
}

void blowfish_decrypt(uint32_t *left, uint32_t *right) {
    uint32_t L = *left;
    uint32_t R = *right;

    for (int i = N + 1; i > 1; i--) {
        L ^= P[i];
        R ^= F(L);
        uint32_t temp = L;
        L = R;
        R = temp;
    }
    uint32_t temp = L;
    L = R;
    R = temp;

    R ^= P[1];
    L ^= P[0];

    *left = L;
    *right = R;
}

void print_block(uint32_t left, uint32_t right) {
    printf("%08X %08X\n", left, right);
}

// Função CBC para criptografar
void blowfish_encrypt_cbc(uint8_t *data, size_t len, uint32_t iv_left, uint32_t iv_right) {
    for (size_t i = 0; i < len; i += 8) {
        uint32_t left = 0, right = 0;
        memcpy(&left, data + i, 4);
        memcpy(&right, data + i + 4, 4);

        // CBC: XOR com IV ou bloco anterior
        left ^= iv_left;
        right ^= iv_right;

        blowfish_encrypt(&left, &right);

        // Salva bloco cifrado
        memcpy(data + i, &left, 4);
        memcpy(data + i + 4, &right, 4);

        // Atualiza IV para próximo bloco
        iv_left = left;
        iv_right = right;
    }
}

// Função CBC para descriptografar
void blowfish_decrypt_cbc(uint8_t *data, size_t len, uint32_t iv_left, uint32_t iv_right) {
    for (size_t i = 0; i < len; i += 8) {
        uint32_t left = 0, right = 0, c_left = 0, c_right = 0;
        memcpy(&left, data + i, 4);
        memcpy(&right, data + i + 4, 4);

        c_left = left;
        c_right = right;

        blowfish_decrypt(&left, &right);

        // CBC: XOR com IV ou bloco anterior cifrado
        left ^= iv_left;
        right ^= iv_right;

        // Salva bloco decifrado
        memcpy(data + i, &left, 4);
        memcpy(data + i + 4, &right, 4);

        // Atualiza IV para próximo bloco
        iv_left = c_left;
        iv_right = c_right;
    }
}

int main() {
    char frase[256];
    printf("Digite uma frase (até 255 caracteres):\n");
    fgets(frase, sizeof(frase), stdin);

    size_t len = strlen(frase);
    if (frase[len - 1] == '\n') frase[len - 1] = '\0';
    len = strlen(frase);

    // Padding para múltiplo de 8 bytes
    size_t padded_len = ((len + 7) / 8) * 8;
    uint8_t *buffer = calloc(padded_len, 1);
    memcpy(buffer, frase, len);

    // Vetor de inicialização (IV) fixo para exemplo
    uint32_t iv_left = 0x12345678;
    uint32_t iv_right = 0x9ABCDEF0;

    printf("\nTexto original (hex):\n");
    for (size_t i = 0; i < padded_len; i += 8) {
        uint32_t left = 0, right = 0;
        memcpy(&left, buffer + i, 4);
        memcpy(&right, buffer + i + 4, 4);
        print_block(left, right);
    }

    blowfish_encrypt_cbc(buffer, padded_len, iv_left, iv_right);

    printf("\nCriptografado (hex):\n");
    for (size_t i = 0; i < padded_len; i += 8) {
        uint32_t left = 0, right = 0;
        memcpy(&left, buffer + i, 4);
        memcpy(&right, buffer + i + 4, 4);
        print_block(left, right);
    }

    blowfish_decrypt_cbc(buffer, padded_len, iv_left, iv_right);

    printf("\nDescriptografado:\n");
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}