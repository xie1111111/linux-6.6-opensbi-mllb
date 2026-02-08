ENTRY(main)
MEMORY {
    ram : ORIGIN = 0x80200000, LENGTH = 0x20000000
}
SECTIONS {
    . = 0x80200000;
    .text : { *(.text) } > ram
    .data : { *(.data) } > ram
    .bss : { *(.bss) } > ram
}