
# Compile
```bash
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 ../stm32L4R5ZIT6PU_startup.c -o stm32L4R5ZIT6PU_startup.o
arm-none-eabi-gcc -nostdlib -T ../stm32_ls.ld *.o -o blink_2.elf
```

# Flash
```bash
openocd -f board/st_nucleo_l4.cf
```

```bash
arm-none-eabi-gdb
# > monitor reset init
# > monitor flash write_image erase blink_2.elf
# > monitor reset init
# > monitor resume
```
