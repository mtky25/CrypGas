ENTRY(_start)

SECTIONS {
    . = 0x8000;

    .text : {
        *(.text)
    }
    .rodata : {
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
    }

    . = . + 0x1000;
    stack_top = .;
}
