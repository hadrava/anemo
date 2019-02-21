PROJECT = main

OBJECTS = main.o

MMCU    = attiny25
PART    = t25
CFLAGS  = -MMD -Wall -Os -finline-functions -std=gnu11
CFLAGS += -DF_CPU=8000000 -mmcu=$(MMCU)
AVRDUDEFLAGS  = -p $(PART) -c usbasp -v
HFUSE = 0xDF   # Default H-FUSE
#LFUSE = 0x62   # 8 MHz / 8 = Default L-FUSE
LFUSE = 0xE2   # 8 MHz L-FUSE


CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

ASM = $(CC)
ASFLAGS = -mmcu=$(MMCU) -I /usr/lib/avr/include/


HEX = $(PROJECT).hex
ELF = $(PROJECT).elf

DEPENDENCIES=$(OBJECTS:.o=.d)

all: $(HEX)

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(ASM) $(ASFLAGS) -c $< -o $@

$(ELF): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

flash: $(HEX)
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$<

flash-lfuse:
	$(AVRDUDE) $(AVRDUDEFLAGS) -U "lfuse:w:$(LFUSE):m"

flash-hfuse:
	$(AVRDUDE) $(AVRDUDEFLAGS) -U "hfuse:w:$(HFUSE):m"

read-fuse: restart

restart:
	$(AVRDUDE) $(AVRDUDEFLAGS)

clean::
	rm -f $(HEX) $(ELF) $(OBJECTS) $(DEPENDENCIES)

-include $(DEPENDENCIES)

.PHONY: all flash flash-lfuse flash-hfuse read-fuse clean
