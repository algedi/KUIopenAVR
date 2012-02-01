#########      AVR Project Makefile        #########
######                                        ######
######          Algedi project (c)            ######
###### -------------------------------------  ######
######            License: GPLv3              ######
###### -------------------------------------  ######
######        KK   KK  UU      UU  II         ######
######        KK  KK   UU      UU  II         ######
######        KK KK    UU      UU  II         ######
######        KKKK     UU      UU  II         ######
######        KK KK    UU      UU  II         ######
######        KK  KK    UU    UU   II         ######
######        KK   KK     UUUU     II         ######
######                                        ######
####################################################
######              UTILITY                   ######
####################################################

# AVR-GCC Makefile

MCU=atmega328p
CC=avr-c++
OBJ2HEX=avr-objcopy

PROJECT=main
SOURCES=main.cpp wiring.c Servo.cpp
INC=.

LIBS=
CFLAGS=-I$(INC) -mmcu=$(MCU) -Wall
AVRDUDE_PROGRAMMERID=usbtiny
AVRDUDE_PORT=/dev/ttyS0
AVRDUDE_MCU=m8
F_CPU=16000000UL


Servo.o: Servo.cpp
	$(CC) $(CFLAGS) $< -o $@

#flash:
#	avrdude -c usbtiny -p m328p -U flash:w:main.hex

clean:
	rm -f *.o
	rm -f *.hex




#####################
###   REFERENCE   ###
#####################

# atmega103
# atmega128
# atmega1280
# atmega1281
# atmega1284p
# atmega16
# atmega161
# atmega162
# atmega163
# atmega164a
# atmega164p
# atmega165
# atmega165a
# atmega165p
# atmega168
# atmega168a
# atmega168p
# atmega16a
# atmega2560
# atmega2561
# atmega32
# atmega323
# atmega324a
# atmega324p
# atmega324pa
# atmega325
# atmega325a
# atmega325p
# atmega3250
# atmega3250a
# atmega3250p
# atmega328
# atmega328p
# atmega48
# atmega48a
# atmega48p
# atmega64
# atmega640
# atmega644
# atmega644a
# atmega644p
# atmega644pa
# atmega645
# atmega645a
# atmega645p
# atmega6450
# atmega6450a
# atmega6450p
# atmega8
# atmega88
# atmega88a
# atmega88p
# atmega88pa
# atmega8515
# atmega8535




