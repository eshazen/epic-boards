#
# Makefile for blinky
#

MCU = attiny85
# MCU = atmega328

# 8 MHz for on-board oscillator
F_OSC = 8000000

# 16MHz for Stock arduino
# F_OSC = 16000000

CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_min -lm
# no-optimization settings for interrupt code
CFLAGS_NOOPT = -g -O0 -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -I../util -Wl,-u,vfprintf -lprintf_min

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

# FUSEOPT = -U hfuse:w:0xd9:m

# disable CLKDIV8 on ATTiny85
FUSEOPT = -U lfuse:w:0xe2:m

# programmer configuration for avrdude programming utility

# for AVRISP programmer on USB
DUDEPORT  = -c avrispv2 -P usb

# "Tiny AVR programmer"
# DUDEPORT = -c usbtiny -b 19200

# for Arduino bootloader
# DUDEPORT  = -c arduino -P /dev/ttyACM0

# DUDEMCU = m328p
DUDEMCU = t85
AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = main.o light_ws2812.o
asmobj =

headers = rgb32.h light_ws2812.h ws2812_config.h


all: $(asmobj) $(objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

flash: main.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S main.elf > main.lst
	avr-size --common -x main.elf

$(objects): %.o: %.c $(headers)
	avr-gcc -c $(CFLAGS) $< -o $@

$(asmobj): %.o: %.s
	avr-gcc -c $(CFLAGS) $< -o $@

main.elf: $(objects)
	avr-gcc $(LDFLAGS) $(asmobj) $(objects) -o $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

fuse:
	$(AVRDUDE) $(FUSEOPT)

rfuse:
	$(AVRDUDE) -U lfuse:r:-:h
