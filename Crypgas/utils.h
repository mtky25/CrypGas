#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void uitoa(uint32_t num, char *str);
void uitox(uint32_t num, char *str, int with_prefix);
void uart_put_ms(uint64_t us);
void uart_put_s(uint64_t us);
int atoi(const char *str);
void buffer_to_hex(const uint8_t *in, uint32_t len, char *out);
uint32_t hex_to_buffer(const char *in, uint8_t *out);

#endif
