.section .text
.global _start

_start:
    cpsid if
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x13     /* modo SVC */
    msr cpsr_c, r0

    ldr sp, =stack_top
    bl main

hang:
    b hang

.align 4
.section .bss
.space 4096
stack_top:
