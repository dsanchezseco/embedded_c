CC = arm-none-eabi-gcc -I .
TARGET_CHIP = -DSTM32L4R5xx
CMSIS = -I chip_headers/CMSIS/Include -I chip_headers/CMSIS/Device/ST/STM32L4xx/Include
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 $(CMSIS) $(TARGET_CHIP)
LDFLAGS = -nostdlib -T ../stm32_ls.ld -Wl,-Map=$@.map


BINARY = blink_2.elf
TARGET_BOARD = st_nucleo_l4.cfg

OBJECTS = main.o gpio.o systick.o stm32L4R5ZIT6PU_startup.o system_stm32l4xx.o

# Compile .c files
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

# Link .o with LinkScript and create binary file
build: $(BINARY)
$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Flash binary to board
.PHONY: flash
flash: $(BINARY)
	openocd -f board/$(TARGET_BOARD)  -c \
		"init; \
		reset halt; \
		sleep 100; \
		flash write_image erase $^; \
		reset run; \
		shutdown"

# delete all generated files
clean:
	rm -f *.o *.elf *.map


rebuild: clean build