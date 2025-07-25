SRCS = boot.s main.c uart.c cesar.c 
OBJS = boot.o main.o uart.o cesar.o 

# # Interface serial
TTY = /dev/ttyUSB0

# Configuração JTAG
OCD_CFG = jtag.cfg

PREFIXO = arm-none-eabi-
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy

# Opções do compilador
CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding

all: kernel.img 

kernel.img: kernel.elf
	${OBJCPY} -O binary $< $@


%.o: %.c 
	${GCC} ${CFLAGS} -c $< -o $@

%.o: %.s	
	${AS} $< -o $@

kernel.elf: ${OBJS}
	${LD} -T linker.ld -o $@ ${OBJS}

clean:
	rm -f *.o *.elf *.img