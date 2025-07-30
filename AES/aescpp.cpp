#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_entrada.txt>\n";
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << argv[1] << "\n";
        return 1;
    }
    std::string plain((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    // chave e inicialization vector aleatórios
    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    byte iv[AES::BLOCKSIZE];
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, sizeof(iv));

    // encrypt
    std::string cipher;
    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    StringSource(plain, true,
        new StreamTransformationFilter(encryptor,
            new StringSink(cipher)
        )
    );

    // formatar hex em pares de bytes
    auto formatHex = [](const std::string& hex) {
        std::string out;
        for (size_t i = 0; i < hex.size(); i += 2) {
            out += hex.substr(i, 2);
            if ((i + 2) < hex.size()) out += ' ';
        }
        return out;
    };

    // chave em hexadecimal
    std::string keyHex;
    StringSource(key, key.size(), true, new HexEncoder(new StringSink(keyHex)));
    std::cout << "\nCipher Key (hex):\n" << formatHex(keyHex) << "\n";

    // plaintext em hexadecimal
    std::string plainHex;
    StringSource(plain, true, new HexEncoder(new StringSink(plainHex)));
    std::cout << "\nPlaintext (hex):\n" << formatHex(plainHex) << "\n";

    // ciphertext em hexadecimal
    std::string cipherHex;
    StringSource(cipher, true, new HexEncoder(new StringSink(cipherHex)));
    std::cout << "\nCiphertext (hex):\n" << formatHex(cipherHex) << "\n";

    // decrypt
    std::string recovered;
    CBC_Mode<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);
    StringSource(cipher, true,
        new StreamTransformationFilter(decryptor,
            new StringSink(recovered)
        )
    );

    // texto descriptografado em hexadecimal
    std::string recoveredHex;
    StringSource(recovered, true, new HexEncoder(new StringSink(recoveredHex)));
    std::cout << "\nDecrypted text (hex):\n" << formatHex(recoveredHex) << "\n";

    // texto descriptografado em ASCII (plaintext original)
    std::cout << "\nDecrypted text (ASCII):\n" << recovered << "\n";

    return 0;
}
