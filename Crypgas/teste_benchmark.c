#include "uart.h"
#include "benchmark.h"
#include <stdint.h>

int main(void) {
    uart_init();
    uart_puts("Teste System Timer (us)\n");
    
    while (1) {
        uint64_t val = benchmark_get_system_timer();  // lê timer em microssegundos

        // Imprime apenas os 32 bits baixos (suficiente para verificar incremento)
        uart_put_uint((uint32_t)val);
        uart_puts("\n");
    }
}