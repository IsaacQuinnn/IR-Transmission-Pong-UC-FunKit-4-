# File:   Makefile
# Authors: Alex Shepherd & Isaac Quinn
# Date:   12 Oct 2026
# Descr:  Makefile for pong

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../drivers/ledmat.h ../../utils/pacer.h paddle.h ball.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/system.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

paddle.o: paddle.c ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/ledmat.h ../../drivers/avr/ir_uart.h paddle.h
	$(CC) -c $(CFLAGS) $< -o $@

ball.o: ball.c ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/ledmat.h ../../drivers/avr/ir_uart.h paddle.h ball.h
	$(CC) -c $(CFLAGS) $< -o $@

start.o: start.c ../../drivers/avr/system.h ../../fonts/font5x7_1.h ../../utils/pacer.h ../../drivers/ledmat.h ../../utils/tinygl.h start.h
	$(CC) -c $(CFLAGS) $< -o $@

end.o: end.c ../../drivers/avr/system.h ../../drivers/ledmat.h ../../utils/tinygl.h end.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o system.o pio.o timer.o pacer.o navswitch.o ledmat.o ir_uart.o usart1.o timer0.o prescale.o display.o font.o tinygl.o ball.o paddle.o start.o end.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start