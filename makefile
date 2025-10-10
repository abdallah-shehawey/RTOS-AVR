# MCU and frequency
MCU = atmega32
F_CPU = 16000000UL

# Compiler and tools
CC = avr-gcc
OBJCOPY = avr-objcopy

# Flags
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -IAPP_Layer -IGIE -IOS -ITIMER

# Source and object files
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)

# Output files
TARGET = main

# Build rules
all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -f */*.o *.elf *.hex

