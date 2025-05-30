/* LINKER SCRIPT */
ENTRY(Reset_Handler)

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 640K
    /* SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
    SRAM2 (rwx) : ORIGIN = 0x20030000, LENGTH = 64K 
    SRAM3 (rwx) : ORIGIN = 0x20040000, LENGTH = 384K */
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2M
}

/* end of the STACK as it grows downwards */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

__max_heap_size = 0x200;
__max_stack_size = 0x400;


SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector_tbl)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    }>FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    }>SRAM AT> FLASH /* stored in FLASH but at SRAM during runtime*/

    .bss : 
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM

}