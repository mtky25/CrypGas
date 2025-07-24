.section .text
.global _start

_start:
    mov r0, #0b10011        // Supervisor mode
    msr cpsr, r0

    ldr sp, =_stack_top     // Inicializa SP

    // Zerar a .bss
    mov r0, #0
    ldr r1, =bss_begin
    ldr r2, =bss_end

loop:
    cmp r1, r2
    bge cont
    str r0, [r1], #4
    b loop

cont:
    bl main

stop:
    b stop
