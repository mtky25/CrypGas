#define UART0_DR  *((volatile unsigned int *)0x09000000) // UART do QEMU virt machine

void uart_putc(char c) {
    UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void cifra_cesar(char *msg, int chave) {
    for (int i = 0; msg[i] != '\0'; i++) {
        char c = msg[i];
        if (c >= 'A' && c <= 'Z') {
            msg[i] = ((c - 'A' + chave) % 26) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            msg[i] = ((c - 'a' + chave) % 26) + 'a';
        }
    }
}

void main() {
    char mensagem[] = "ciao mundo";
    uart_puts("Antes: ");
    uart_puts(mensagem);
    uart_putc('\n');

    cifra_cesar(mensagem, 3);

    uart_puts("Depois: ");
    uart_puts(mensagem);
    uart_putc('\n');

    while (1);
}
