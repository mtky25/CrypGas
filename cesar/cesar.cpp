#include <iostream>
#include <fstream>
#include <string>

std::string cesar(const std::string& text, int shift) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        } else if (isdigit(c)) {
            c = (c - '0' + (shift % 10 + 10) % 10) % 10 + '0';
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " <arquivo_entrada.txt>\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    int chave = 3;

    // Criptografa
    std::string cript = cesar(text, chave);
    std::cout << "Criptografado:\n" << cript << std::endl;

    // Decriptografa
    std::string decript = cesar(cript, 26 - (chave % 26));
    std::cout << "Decriptografado:\n" << decript << std::endl;

    return 0;
}