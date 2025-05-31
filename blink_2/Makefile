CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11
LDFLAGS = -nostdlib -T ../stm32_ls.ld -Wl,-Map=$@.map

BINARY = blink_2.elf
TARGET_BOARD = st_nucleo_l4.cfg

OBJECTS = main.o stm32L4R5ZIT6PU_startup.o

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