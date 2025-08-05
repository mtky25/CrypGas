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
void buffer_to_hex(const uint8_t *in, uint32_t len, char *out) {
    const char hex_chars[] = "0123456789ABCDEF";
    for (uint32_t i = 0; i < len; i++) {
        out[i * 2] = hex_chars[(in[i] >> 4) & 0x0F];
        out[i * 2 + 1] = hex_chars[in[i] & 0x0F];
    }
    out[len * 2] = '\0';
}

uint32_t hex_to_buffer(const char *in, uint8_t *out) {
    uint32_t len = 0;
    while (in[0] && in[1]) {
        uint8_t high = (in[0] <= '9') ? in[0] - '0' : (in[0] & ~0x20) - 'A' + 10;
        uint8_t low  = (in[1] <= '9') ? in[1] - '0' : (in[1] & ~0x20) - 'A' + 10;
        out[len++] = (high << 4) | low;
        in += 2;
    }
    return len;
}
