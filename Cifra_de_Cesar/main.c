#include "cesar.h"
#include "uart.h"

void main(void) {
    uart_init();

    char buffer[100];
    char c = 0;
    int i = 0;

    uart_puts("Pronto para receber (digite '|' sozinho para sair):\r\n");

    while (1) {
        i = 0;

        while (1) {
            c = uart_get();

            // Trata backspace ou DEL
            if (c == '\b' || c == 127) {
                if (i > 0) {
                    i--;                // remove último caractere do buffer
                    uart_puts("\b \b"); // move cursor para trás, apaga e volta
                }
                continue;
            }

            // Ecoa caractere normal
            uart_send(c);

            // Se for Enter, termina a entrada
            if (c == '\r' || c == '\n') {
                break;
            }

            // Armazena no buffer se houver espaço
            if (i < sizeof(buffer) - 1) {
                buffer[i++] = c;
            }
        }

        buffer[i] = '\0'; // termina a string

        // Se a mensagem for apenas "|", encerra
        if (i == 1 && buffer[0] == '|') {
            uart_puts("\r\nEncerrando...\r\n");
            break;
        }

        // Aplica cifra de César
        apply_cifra(buffer, 3);

        // Mostra resposta
        uart_puts("\r\nResposta:\r\n");
        uart_puts(buffer);
        uart_puts("\r\n");
    }

    while (1); // trava aqui após encerrar
}
