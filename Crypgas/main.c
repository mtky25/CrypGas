#include "crypgas.h"
#include "uart.h"
#include "benchmark.h"
#include <string.h>

unsigned heap_svr = 0;

int main(void) {
    uart_init();

    char buffer[100];
    char output[100];
    char c = 0;
    int i = 0;
    int escolha = 0;
    uart_puts("Escolha algoritmo de Criptografia:\r\n");

    // Menu de escolha
    while (escolha < 1 || escolha > 4) {
        uart_puts("Escolha algoritmo de Criptografia:\r\n");
        uart_puts("1 - Cifra de Cesar\r\n");
        uart_puts("2 - AES\r\n");
        uart_puts("3 - DES\r\n");
        uart_puts("4 - Blowfish\r\n");
        escolha = uart_get() - '0';  // converte de ASCII para int
        if (escolha < 1 || escolha > 4)
            uart_puts("Valor inválido. Tente novamente.\r\n");
    }

    uart_puts("Pronto para receber (digite '|' sozinho para sair):\r\n");

    while (1) {
        i = 0;

        // Ler entrada
        while (1) {
            c = uart_get();

            if (c == '\b' || c == 127) {
                if (i > 0) {
                    i--;
                    uart_puts("\b \b");
                }
                continue;
            }

            uart_send(c);

            if (c == '\r' || c == '\n') {
                break;
            }

            if (i < sizeof(buffer) - 1) {
                buffer[i++] = c;
            }
        }

        buffer[i] = '\0';

        if (i == 1 && buffer[0] == '|') {
            uart_puts("\r\nEncerrando...\r\n");
            break;
        }

        uint32_t start = benchmark_get_cycles();
        encrypt((crypto_algorithm_t)escolha, (uint8_t*)buffer, (uint8_t*)output, i);
        uint32_t end = benchmark_get_cycles();

        // benchmark
        uint32_t ciclos = end - start;
        uint32_t tempo_us = benchmark_cycles_to_us(ciclos);
        uint32_t throughput = benchmark_calc_throughput(i, ciclos);

        // Mostra resultado criptografado
        uart_puts("\r\nResposta:\r\n");
        uart_puts(output);
        uart_puts("\r\n");

        // Mostra benchmark
        char msg[20];

        uart_puts("Ciclos: ");
        uitoa(ciclos, msg);
        uart_puts(msg);
        uart_puts("\r\n");

        uart_puts("Tempo (us): ");
        uitoa(tempo_us, msg);
        uart_puts(msg);
        uart_puts("\r\n");

        uart_puts("Throughput (B/s): ");
        uitoa(throughput, msg);
        uart_puts(msg);
        uart_puts("\r\n");
    }

    while (1);
}
