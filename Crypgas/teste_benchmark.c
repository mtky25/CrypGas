#include "uart.h"
#include "benchmark.h"
#include "utils.h"
#include <stdint.h>

int main(void) {
    uart_init();
    uart_puts("Teste Benchmark CNTVCT\n");

    uint64_t start, end;

    // Inicia benchmark
    benchmark_start(&start);

    // Código para medir (loop simples)
    volatile uint32_t sum = 0;
    for (uint32_t i = 0; i < 1000000; i++) {
        sum += i ^ 0x55AA55AA;
    }

    // Finaliza benchmark
    benchmark_end(&end);

    uint64_t cycles = end - start;
    float tempo_us = benchmark_cycles_to_microseconds(cycles);
    float throughput = benchmark_calc_throughput(sizeof(sum), cycles);

    // Converte valores para string antes de enviar pela UART
    char buffer[32];

    uart_puts("Ciclos: ");
    uitoa((uint32_t)cycles, buffer);
    uart_puts(buffer);
    uart_puts("\n");

    uart_puts("Tempo (us): ");
    uitoa((uint32_t)tempo_us, buffer);
    uart_puts(buffer);
    uart_puts("\n");

    uart_puts("Throughput (B/s): ");
    uitoa((uint32_t)throughput, buffer);
    uart_puts(buffer);
    uart_puts("\n");

    while (1);
}
