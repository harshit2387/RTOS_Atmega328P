MCU = atmega328p
F_CPU = 16000000UL
TARGET = kernel_app

CC = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=gnu99 -I./kernel
LDFLAGS = -Wl,--section-start=.text=0x7C00  # Optional: place in boot section

SRC = main.c kernel/scheduler.c kernel/timer.c kernel/uart.c kernel/tasks.c

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	avrdude -c arduino -p m328p -P COM3 -b 115200 -U flash:w:$(TARGET).hex

clean:
	rm -f *.hex *.elf

