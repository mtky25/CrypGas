.global _start
.section .text

_start:
    ldr sp, =_stack_top
    bl main

hang:
    b hang