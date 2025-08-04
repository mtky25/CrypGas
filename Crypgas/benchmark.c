#include "benchmark.h"
#include <stdint.h>

#define SYSTEM_TIMER_BASE 0x3F003000
#define SYSTEM_TIMER_CLO  (SYSTEM_TIMER_BASE + 0x04)
#define SYSTEM_TIMER_CHI  (SYSTEM_TIMER_BASE + 0x08)

/* Leitura de 64 bits do System Timer */
uint64_t benchmark_get_system_timer(void) {
    uint32_t hi, lo;
    do {
        hi = *(volatile uint32_t*)SYSTEM_TIMER_CHI;
        lo = *(volatile uint32_t*)SYSTEM_TIMER_CLO;
    } while (hi != *(volatile uint32_t*)SYSTEM_TIMER_CHI);
    return ((uint64_t)hi << 32) | lo;
}

void benchmark_start(uint64_t *start) {
    *start = benchmark_get_system_timer();
}

void benchmark_end(uint64_t *end) {
    *end = benchmark_get_system_timer();
}

float benchmark_us_to_seconds(uint64_t us) {
    return (float)us / 1000000.0f;
}

float benchmark_calc_throughput(uint32_t bytes, uint64_t us) {
    float tempo_s = benchmark_us_to_seconds(us);
    if (tempo_s == 0.0f) return 0.0f;
    return (float)bytes / tempo_s;
}
