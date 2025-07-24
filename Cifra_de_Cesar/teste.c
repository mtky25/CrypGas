#define UART0_DR  *((volatile unsigned int *)0x09000000) // UART do QEMU virt machine

void uart_putc(char c) {
    UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void main() {
    uart_puts("Boseta");
    while (1);
}