#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// Converte inteiro para string decimal
void uitoa(uint32_t num, char *str);

// Converte inteiro para string hexadecimal (prefixo "0x" opcional)
void uitox(uint32_t num, char *str, int with_prefix);

#endif
