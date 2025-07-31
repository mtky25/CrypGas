#ifndef BLOWFISH_H
#define BLOWFISH_H

void blowfish_encrypt(uint32_t *left, uint32_t *right);
void blowfish_decrypt(uint32_t *left, uint32_t *right);
void print_block(uint32_t left, uint32_t right);
void blowfish_encrypt_cbc(uint8_t *data, size_t len, uint32_t iv_left, uint32_t iv_right);
void blowfish_decrypt_cbc(uint8_t *data, size_t len, uint32_t iv_left, uint32_t iv_right);

#endif