#include "benchmark.h"

/* Habilita o contador de ciclos (PMCCNTR) */
void benchmark_init(void) {
    uint32_t value = 0;

    // Permite acesso a PMU em modo usuário
    __asm__ volatile("MCR p15, 0, %0, c9, c14, 0" : : "r"(1));

    // Liga PMU e reseta contadores
    __asm__ volatile(
        "MRC p15, 0, %0, c9, c12, 0" 
        : "=r"(value)
    );
    value |= 1;        // enable all counters
    value |= (1 << 1); // reset cycle counter
    value |= (1 << 2); // reset event counters

    __asm__ volatile(
        "MCR p15, 0, %0, c9, c12, 0" 
        : : "r"(value)
    );

    // Ativa o contador de ciclos (bit 31)
    value = 1 << 31;
    __asm__ volatile(
        "MCR p15, 0, %0, c9, c12, 1"
        : : "r"(value)
    );
}

/* Lê o contador de ciclos (PMCCNTR) */
uint32_t benchmark_get_cycles(void) {
    uint32_t cc;
    __asm__ volatile("MRC p15, 0, %0, c9, c13, 0" : "=r"(cc));
    return cc;
}

/* Converte ciclos para microssegundos */
uint32_t benchmark_cycles_to_us(uint32_t cycles) {
    return cycles / (CPU_FREQ_HZ / 1000000UL);  // ciclos / 900
}

/* Calcula throughput em bytes/segundo */
uint32_t benchmark_calc_throughput(uint32_t bytes, uint32_t cycles) {
    double tempo_s = (double)cycles / CPU_FREQ_HZ;
    return (uint32_t)(bytes / tempo_s); // bytes por segundo
}