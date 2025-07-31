void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize, size_t expandedKeySize);

// Implementation: AES Encryption

// Implementation: subBytes
void subBytes(unsigned char *state);
// Implementation: shiftRows
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);
// Implementation: addRoundKey
void addRoundKey(unsigned char *state, unsigned char *roundKey);
// Implementation: mixColumns
unsigned char galois_multiplication(unsigned char a, unsigned char b);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
// Implementation: AES round
void aes_round(unsigned char *state, unsigned char *roundKey);
// Implementation: the main AES body
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
// Implementation: AES encryption
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
// AES Decryption
void invSubBytes(unsigned char *state);
void invShiftRows(unsigned char *state);
void invShiftRow(unsigned char *state, unsigned char nbr);
void invMixColumns(unsigned char *state);
void invMixColumn(unsigned char *column);
void aes_invRound(unsigned char *state, unsigned char *roundKey);
void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
