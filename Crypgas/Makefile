ALVO = output
SRCS = main.c crypgas.c uart.c blowfish.c aes.c cesar.c benchmark.c stubs.c utils.c
OBJS = boot.o main.o crypgas.o uart.o blowfish.o aes.o cesar.o benchmark.o stubs.o utils.o

LDOPTS = -L/usr/lib/arm-none-eabi/newlib -lc_nano -lm -L/usr/lib/gcc/arm-none-eabi/13.2.1 -lgcc


OPTS = -march=armv7-a -mtune=cortex-a7 
# # Interface serial
TTY = /dev/ttyUSB0

# Configuração JTAG
OCD_CFG = jtag.cfg

PREFIXO = arm-none-eabi-
AS = ${PREFIXO}as
MAP = ${ALVO}.map
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy

# Opções do compilador
CFLAGS = -Wall -O2 #-nostdlib -nostartfiles -ffreestanding

all: kernel.img

kernel.img: kernel.elf
	${OBJCPY} -O binary $< $@

%.o: %.c
	${GCC} ${CFLAGS} -c $< -o $@

%.o: %.s
	${AS} $< -o $@

kernel.elf: ${OBJS}
	${LD} -T linker.ld -o $@ ${OBJS} ${LDOPTS}


clean:
	rm -f *.o *.elf *.img