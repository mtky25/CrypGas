#include "utils.h"
#include "uart.h"

void uitoa(uint32_t num, char *str) {
    char buffer[11];  
    int i = 0;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Inverter string
    int j = 0;
    while (i > 0) {
        str[j++] = buffer[--i];
    }
    str[j] = '\0';
}


void uitox(uint32_t num, char *str, int with_prefix) {
    char buffer[9]; 
    const char hex_digits[] = "0123456789ABCDEF";
    int i = 0;

    if (num == 0) {
        if (with_prefix) {
            str[0] = '0';
            str[1] = 'x';
            str[2] = '0';
            str[3] = '\0';
        } else {
            str[0] = '0';
            str[1] = '\0';
        }
        return;
    }

    while (num > 0) {
        buffer[i++] = hex_digits[num & 0xF];
        num >>= 4;
    }

    int j = 0;
    if (with_prefix) {
        str[j++] = '0';
        str[j++] = 'x';
    }

    while (i > 0) {
        str[j++] = buffer[--i];
    }

    str[j] = '\0';
}

/* Implementação simples de atoi */
int atoi(const char *str) {
    int result = 0;
    int sign = 1;

    // Ignora espaços
    while (*str == ' ') str++;

    // Verifica sinal
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Converte dígitos
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}
