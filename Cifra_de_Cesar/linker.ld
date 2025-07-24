ENTRY(_start)

SECTIONS {
    . = 0x4000000;

    .text : {
        *(.text*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        bss_begin = .;
        *(.bss*)
        *(COMMON)
        bss_end = .;
    }

    . = ALIGN(8);
    _stack_top = . + 0x1000;
}
