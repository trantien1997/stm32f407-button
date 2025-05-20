# Compiler and flags
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# CFLAGS  = -DSTM32F407xx -mcpu=cortex-m4 -mthumb -O0 -g -Wall -Iinclude -ffreestanding -DMODE1
CFLAGS  = -DSTM32F407xx -mcpu=cortex-m4 -mthumb -O0 -g -Wall -Iinclude -ffreestanding
LDFLAGS = -T linker/stm32f407.ld -nostartfiles -nostdlib -Wl,-Map=blink.map

# Source files
SRCS = src/main.c src/system_stm32f4xx.c src/syscalls.c startup/startup_stm32f407xx.s
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

# Output
TARGET = blink.elf
BIN = blink.bin

all: $(BIN)

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(BIN) blink.map
