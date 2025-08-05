#include "crypgas.h"
#include "uart.h"
#include "benchmark.h"
#include <string.h>
#include "utils.h"

#define TEST_SIZE 8192
#define DEFAULT_SIZE 8000
char buffer[TEST_SIZE];
char output[TEST_SIZE];
unsigned heap_svr = 0;

/* Gera dados para o benchmark */
void fill_input(uint64_t type, uint64_t size) {
    const char pattern[] = "ABC123";
    const char text[] = "O rapido marrom raposo salta sobre o cachorro preguiçoso. ";

    switch (type) {
        case 1: // Massa uniforme (A)
            for (uint64_t i = 0; i < size; i++) buffer[i] = 'A';
            break;

        case 2: // Padrão curto repetitivo
            for (uint64_t i = 0; i < size; i++) buffer[i] = pattern[i % (sizeof(pattern) - 1)];
            break;

        case 3: // Texto real
            for (uint64_t i = 0; i < size; i++) buffer[i] = text[i % (sizeof(text) - 1)];
            break;

        case 4: // Alternando bits
            for (uint64_t i = 0; i < size; i++) buffer[i] = (i % 2 == 0) ? 'A' : 'B';
            break;

        default:
            for (uint64_t i = 0; i < size; i++) buffer[i] = 'A';
            break;
    }
    buffer[size] = '\0';
}

int main(void) {
    uart_init();

    uint64_t escolha = 0;
    uint64_t modo = 0;
    uint64_t tipo_input = 0;
    uint64_t tamanho = DEFAULT_SIZE;
    uint64_t i = 0;
    uint64_t operacao = 0; // 1 - Criptografar, 2 - Descriptografar

    /* Escolha do algoritmo */
    uart_puts("Escolha algoritmo de Criptografia:\r\n");
    uart_puts("1 - Cifra de Cesar\r\n");
    uart_puts("2 - AES\r\n");
    uart_puts("3 - Blowfish\r\n");
    while (escolha < 1 || escolha > 3) {
        escolha = uart_get() - '0'; 
    }

    /* Escolha da operação */
    uart_puts("\r\nEscolha a operacao:\r\n");
    uart_puts("1 - Criptografar\r\n");
    uart_puts("2 - Descriptografar\r\n");
    while (operacao < 1 || operacao > 2) {
        operacao = uart_get() - '0';
    }

    /* Escolha do modo */
    uart_puts("\r\nEscolha o modo:\r\n");
    uart_puts("1 - Input manual\r\n");
    uart_puts("2 - Benchmark automatico\r\n");
    while (modo < 1 || modo > 2) {
        modo = uart_get() - '0';
    }

    /* Se benchmark, escolher tipo de input */
    if (modo == 2) {
        uart_puts("\r\nEscolha tipo de input:\r\n");
        uart_puts("1 - Massa uniforme (A)\r\n");
        uart_puts("2 - Padrao curto repetitivo (ABC123)\r\n");
        uart_puts("3 - Texto real (frases)\r\n");
        uart_puts("4 - Alternando bits (A / B)\r\n");
        while (tipo_input < 1 || tipo_input > 4) {
            tipo_input = uart_get() - '0'; 
        }
    }

    uart_puts("\r\nPronto para iniciar:\r\n");

    while (1) {
        i = 0;

        if (modo == 1) {
            /* Input manual */
            uart_puts("Digite o texto (use '|' para sair e ENTER para enviar):\r\n");
            char c;
            while (1) {
                c = uart_get();

                if ((c == '\b' || c == 127) && i > 0) {  // Backspace
                    i--;
                    uart_puts("\b \b");
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
        } else {
            /* Benchmark automático sempre 8000 bytes */
            fill_input(tipo_input, tamanho);
            i = tamanho;
        }

        uint64_t start, end;
        memset(output, 0, sizeof(output));

        benchmark_start(&start);
        benchmark_end(&end);
        /* Criptografar */
        if (operacao == 1) {
            benchmark_start(&start);
            uint32_t result_len = encrypt((crypto_algorithm_t)escolha,
                                          (uint8_t*)buffer,
                                          (uint8_t*)output,
                                          (uint32_t)i);
            benchmark_end(&end);
            if (escolha == ALG_CESAR) {
                /* César: imprime texto puro */
                uart_puts("\r\nResposta (Texto):\r\n");
                uart_puts(output);
                uart_puts("\r\n");
            } else {
                /* AES / Blowfish: imprime HEX */
                char hex_output[TEST_SIZE * 2 + 1];
                buffer_to_hex((uint8_t*)output, result_len, hex_output);

                uart_puts("\r\nResposta (HEX):\r\n");
                uart_puts(hex_output);
                uart_puts("\r\n");
            }
        } 
        /* Descriptografar */
        else {
            if (escolha == ALG_CESAR) {
                benchmark_start(&start);
                uint32_t result_len = decrypt((crypto_algorithm_t)escolha,
                        (uint8_t*)buffer,
                        (uint8_t*)output,
                        (uint32_t)i);
                benchmark_end(&end);
                        
                output[result_len] = '\0';
                uart_puts("\r\nResposta (Texto):\r\n");
                uart_puts(output);
                uart_puts("\r\n");
            } else {
                /* AES / Blowfish: HEX -> binário -> decrypt */
                uint8_t bin_input[TEST_SIZE];
                uint32_t bin_len = hex_to_buffer(buffer, bin_input);

                uint32_t result_len = decrypt((crypto_algorithm_t)escolha,
                                              (uint8_t*)bin_input,
                                              (uint8_t*)output,
                                              bin_len);

                output[result_len] = '\0';
                uart_puts("\r\nResposta (Texto):\r\n");
                uart_puts(output);
                uart_puts("\r\n");
            }
        }



        uint64_t tempo_us = end - start;
        float throughput = benchmark_calc_throughput(i, tempo_us);

        /* Mostra resultado */
        uart_puts("Tempo (us): ");
        char msg[32];
        uitoa(tempo_us, msg);
        uart_puts(msg);
        uart_puts("\r\n");

        uart_puts("Throughput (B/s): ");
        uitoa((uint32_t)throughput, msg);
        uart_puts(msg);
        uart_puts("\r\n");

        if (modo == 2) {
            uart_puts("Benchmark finalizado.\r\n");
            break;
        }
    }

    while (1);
}
