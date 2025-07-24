FONTES = teste_startup.s teste.c
ALVO = teste

# # Interface serial
# TTY = /dev/ttyUSB0

# Configuração JTAG
OCD_CFG = jtag.cfg

# Arquivos de saída
EXEC = ${ALVO}.elf
MAP = ${ALVO}.map
IMAGE = ${ALVO}.img
HEXFILE = ${ALVO}.hex
LIST = ${ALVO}.list
OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

PREFIXO = arm-none-eabi-
LDSCRIPT = linker.ld
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

# Opções do compilador
OPTS = -march=armv7-a -mtune=cortex-a15 -g -O0 -ffreestanding -nostdlib

# Linkagem (sem libc)
LDOPTS = -g

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

# Gerar executável
${EXEC}: ${OBJETOS}
	${LD} -T ${LDSCRIPT} -Map=${MAP} -o $@ ${OBJETOS} ${LDOPTS}

# Gerar imagem binária
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}

# Gerar Intel Hex
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

# Gerar listagem
${LIST}: ${EXEC}
	${OBJDMP} -d ${EXEC} > ${LIST}

# Compilar arquivos C
.c.o:
	${GCC} ${OPTS} -c -o $@ $<

# Montar arquivos Assembler
.s.o:
	${AS} -g -o $@ $<

# Limpar tudo
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE} ${HEXFILE}

#
# Iniciar QEMU em modo texto com UART no terminal
#
qemu: ${EXEC}
	@if ps -ax | awk '{print $$5}' | grep '^qemu-system-arm' >/dev/null ; then\
		echo "qemu já está executando"; \
	else qemu-system-arm -s -M virt -nographic -kernel ${ALVO}.img & \
	fi

#
# Iniciar GDB remoto
#
gdb: ${EXEC}
	gdb-multiarch -ex "target extended-remote :1234" \
					  -ex "load" \
					  ${EXEC}

#
# Forçar encerramento
#
kill:
	@-killall qemu-system-arm 2>/dev/null
	@-killall gdb-multiarch 2>/dev/null
