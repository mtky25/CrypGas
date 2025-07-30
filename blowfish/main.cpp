/*
#include <cryptopp/blowfish.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <iostream>

using namespace CryptoPP;

int main() {
    byte key[Blowfish::DEFAULT_KEYLENGTH] = {'k','e','y'};
    byte plaintext[] = "Texto claro";
    byte ciphertext[128], decrypted[128];

    ECB_Mode<Blowfish>::Encryption e;
    e.SetKey(key, sizeof(key));
    e.ProcessData(ciphertext, plaintext, sizeof(plaintext));

    ECB_Mode<Blowfish>::Decryption d;
    d.SetKey(key, sizeof(key));
    d.ProcessData(decrypted, ciphertext, sizeof(plaintext));

    std::cout << decrypted << std::endl;
    return 0;
}
    */