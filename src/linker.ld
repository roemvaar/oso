ENTRY(_start)
SECTIONS {
    . = 0x80000;    /* start text at this location */
    .text.boot : {
        KEEP(*(.text.boot)) /* boot code must come first */
    }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}
