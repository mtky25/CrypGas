#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>

/* Marca início e fim da medição */
void benchmark_start(uint64_t *start);
void benchmark_end(uint64_t *end);

/* Converte microssegundos para segundos */
float benchmark_us_to_seconds(uint64_t us);

/* Calcula throughput (bytes/s) a partir de tempo em us */
float benchmark_calc_throughput(uint32_t bytes, uint64_t us);

/* Função para leitura bruta do System Timer */
uint64_t benchmark_get_system_timer(void);

#endif
