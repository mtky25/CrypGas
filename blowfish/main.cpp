
#include <cryptopp/blowfish.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace CryptoPP;

int main(int argc, char* argv[]) {
    const char* filename = argc > 1 ? argv[1] : "text.txt";
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        return 1;
    }
    std::vector<byte> plaintext((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Padding para múltiplo de 8 bytes
    size_t padded_len = ((plaintext.size() + 7) / 8) * 8;
    plaintext.resize(padded_len, 0);

    byte key[16] = {'k','k','k','k','e','e','e','e','y','y','y','y','.','.','.','.'};
    byte iv[8] = {0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0};

    std::vector<byte> ciphertext(padded_len);
    std::vector<byte> decrypted(padded_len);

    // CBC Encryption
    CryptoPP::CBC_Mode<Blowfish>::Encryption enc;
    enc.SetKeyWithIV(key, sizeof(key), iv);
    enc.ProcessData(ciphertext.data(), plaintext.data(), padded_len);

    // CBC Decryption
    CryptoPP::CBC_Mode<Blowfish>::Decryption dec;
    dec.SetKeyWithIV(key, sizeof(key), iv);
    dec.ProcessData(decrypted.data(), ciphertext.data(), padded_len);

    std::cout << "Texto original (hex):\n";
    for (size_t i = 0; i < padded_len; ++i) {
        printf("%02X%s", plaintext[i], ((i+1)%8)?" ":"\n");
    }
    std::cout << "\nCriptografado (hex):\n";
    for (size_t i = 0; i < padded_len; ++i) {
        printf("%02X%s", ciphertext[i], ((i+1)%8)?" ":"\n");
    }
    std::cout << "\nDescriptografado:\n";
    std::cout.write(reinterpret_cast<char*>(decrypted.data()), plaintext.size());
    std::cout << std::endl;
    return 0;
}