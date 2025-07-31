#include <stdint.h>

#ifndef BENCHMARK_H
#define BENCHMARK_H

// Frequência do CPU do Raspberry Pi 2 (900 MHz)
#define CPU_FREQ_HZ 900000000UL

// Inicializa o contador de ciclos
void benchmark_init(void);

// Retorna o valor atual do contador de ciclos
uint32_t benchmark_get_cycles(void);

// Converte ciclos em microssegundos
uint32_t benchmark_cycles_to_us(uint32_t cycles);

// Calcula throughput em bytes por segundo
uint32_t benchmark_calc_throughput(uint32_t bytes, uint32_t cycles);

#endif 

