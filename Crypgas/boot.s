.section .text
.global _start

_start:
    cpsid i
    ldr sp, =stack_top
    bl main

fim:
    b fim
