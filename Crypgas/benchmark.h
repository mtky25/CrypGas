#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>

void benchmark_start(uint64_t *start);
void benchmark_end(uint64_t *end);
float benchmark_us_to_seconds(uint64_t us);
float benchmark_calc_throughput(uint32_t bytes, uint64_t us);
uint64_t benchmark_get_system_timer(void);

#endif
