.global _start

.section .text
_start:
    /* Desabilita IRQs */
    cpsid i

    /* Zera .bss */
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
bss_clear:
    cmp r0, r1
    itt lt
    strlt r2, [r0], #4
    blt bss_clear

    /* Configura stack pointer (SP) bem acima da bss) */
    ldr sp, =0x80000   /* 512KB de stack - pode ajustar */

    /* Chama main() */
    bl main

hang:
    b hang
