# CrypGas
O CrypGas é um projeto desenvolvido na matéria de Laboratório de Processadores (PCS3732) com foco em desenvolver uma biblioteca de algoritmos de encriptografia em C para serem executados em uma Raspberry Pi 2.

Mais especificamente, este projeto implementa uma **biblioteca de algoritmos de criptografia para a Raspberry Pi 2 em ambiente bare‑metal**, sem sistema operacional. A comunicação ocorre via **UART**, permitindo envio e recebimento de mensagens para teste de diferentes algoritmos diretamente no hardware.

Inicialização e configuração são feitas com um arquivo em **Assembly** e um **linker script** que posiciona o código na memória correta (0x8000). A biblioteca atualmente inclui a **Cifra de César**, mas foi projetada para suportar outros algoritmos no futuro (AES, DES e Blowfish).

## Requisitos
- Raspberry Pi 2 (ou compatível)

- Cabo USB-UART (115200 baud)

- Toolchain ARM: arm-none-eabi-gcc, arm-none-eabi-ld, arm-none-eabi-objcopy

- Utilitário screen para comunicação serial
- usbipd-win no Windows para compartilhar a porta USB com o WSL

- Cartão SD configurado para boot bare-metal

## Estrutura do projeto
### Cifra de César
- boot.s – Código de inicialização, configura pilha e chama main().

- linker.ld – Define o layout da memória e o endereço inicial do código.

- uart.c / uart.h – Rotinas para inicialização e envio/recebimento pela UART.

- cesar.c / cesar.h – Implementação da cifra de César (exemplo inicial da biblioteca).

- main.c – Loop principal: recebe mensagens, aplica criptografia e envia de volta.

- Makefile – Automação de build e geração do binário kernel.img.