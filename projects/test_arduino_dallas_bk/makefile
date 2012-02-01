####################################################
########                                    ########
######         AVR Project Makefile           ######
######                                        ######
######  ------------------------------------  ######
######                                        ######
######            License: GPLv3              ######
######      Algedi project: algedi@tin.it     ######
######                                        ######
######  ------------------------------------  ######
######                                        ######
######        KK   KK  UU      UU  II         ######
######        KK  KK   UU      UU  II         ######
######        KK KK    UU      UU  II         ######
######        KKKK     UU      UU  II         ######
######        KK KK    UU      UU  II         ######
######        KK  KK    UU    UU   II         ######
######        KK   KK     UUUU     II         ######
######                                        ######
####################################################

#MCU=atmega328p
#F_CPU=16000000L
#AVRDUDE_MCU=m328p
#PROGRAMMER=usbtiny


CC=avr-gcc					# Compilatore C
CCpp=avr-c++					# Compilatore C++ (avr-c++)
OBJ2HEX=avr-objcopy
INC=./include
#CFLAGS=-I$(INC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -gdwarf-2 
CFLAGS_C=-I$(INC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) 
CFLAGS_CPP=-I$(INC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) 
CFLAGS_OBJ= -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC)
#CFLAGS_OBJ= -c -g -Os -Wl,--gc-sections -w -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC)
# -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections

AVRDUDE_PORT=/dev/ttyS0
PROJECT=main.cpp

DIR_OBJ=obj
DIR_CORE=cores
DIR_SRC=src
DIR_LIB=lib

CORE_C:=$(wildcard cores/*.c)
CORE_CPP:=$(wildcard cores/*.cpp)
CORE_OBJ_C=$(addprefix obj/, $(notdir $(CORE_C:.c=.o)))
CORE_OBJ_CPP=$(addprefix obj/, $(notdir $(CORE_CPP:.cpp=.o)))
CORE_OBJ=$(CORE_OBJ_C) $(CORE_OBJ_CPP)

LIB_C:=$(wildcard lib/*.c)
LIB_CPP:=$(wildcard lib/*.cpp)
LIB_OBJ_C=$(addprefix obj/, $(notdir $(LIB_C:.c=.o)))
LIB_OBJ_CPP=$(addprefix obj/, $(notdir $(LIB_CPP:.cpp=.o)))
LIB_OBJ=$(LIB_OBJ_C) $(LIB_OBJ_CPP)

SRC_C:=$(wildcard src/*.c)
SRC_CPP:=$(wildcard src/*.cpp)
SRC_OBJ_C=$(addprefix obj/, $(notdir $(SRC_C:.c=.o)))
SRC_OBJ_CPP=$(addprefix obj/, $(notdir $(SRC_CPP:.cpp=.o)))
SRC_OBJ=$(SRC_OBJ_C) $(SRC_OBJ_CPP)


flash: out/main.hex
	@echo "\t>>\twrite FLASH in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  -b $(SERIAL_BAUD)  -U flash:w:$< 2>>out.log
	@echo "\t\twrite FLASH in chip: finish"

out/main.hex: out/main.elf
	@echo "\t>>\tconvert in intelHEX: start"
	@$(OBJ2HEX) -O ihex $< $@ 2>>out.log
	@echo "\t\tconvert in intelHEX: finish"

out/main.elf: obj/src.ar obj/lib.ar
	@echo "\t>>\tlink all: start"
	@$(CC) -g  -Wl,--gc-sections -mmcu=$(MCU) -o out/main.elf obj/src.ar obj/lib.ar 2>>out.log
	@echo "\t\tlink all: finish"

obj/lib.ar: $(LIB_OBJ)
	@echo "\t>>\tlink objects src: start"
	@avr-ar rcs obj/lib.ar $(LIB_OBJ) 2>>out.log
	@echo "\t\tlink objects src: finish"

obj/src.ar: $(SRC_OBJ)
	@echo "\t>>\tlink objects src: start"
	@avr-ar rcs obj/src.ar $(SRC_OBJ) 2>>out.log
	@echo "\t\tlink objects src: finish"

$(LIB_OBJ_CPP):
	@echo "\t>>\tcompile cpp lib: start"
	@$(CCpp) $(CFLAGS_OBJ) -c $(LIB_CPP) 2>>out.log
	@mv *.o $(DIR_OBJ) 
	@echo "\t\tcompile cpp lib: finish"

$(LIB_OBJ_C):
	@echo "\t>>\tcompile c lib: start"
	@$(CC) $(CFLAGS_OBJ) -c $(LIB_C) 2>>out.log
	@mv *.o $(DIR_OBJ) 
	@echo "\t\tcompile c lib: finish"

$(SRC_OBJ_CPP): $(SRC_CPP)
	@echo "\t>>\tcompile cpp source: start"
#	@$(CCpp) $(CFLAGS) -c $(SRC_CPP) 2>>out.log
	@$(CCpp) $(CFLAGS_CPP) -c $(SRC_CPP) 2>>out.log
	@mv *.o $(DIR_OBJ) 
	@echo "\t\tcompile cpp source: finish"

$(SRC_OBJ_C): $(SRC_C)
	@echo "\t>>\tcompile c souce : start"
#	@$(CC) $(CFLAGS) -c $(SRC_C) 2>>out.log
	@$(CC) $(CFLAGS_C) -c $(SRC_C) 2>>out.log
	@mv *.o $(DIR_OBJ) 
	@echo "\t\tcompile c souce: finish"

fuse_h: 
	@echo "\t>>\twrite FUSE_H in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U hfuse:w:$(FUSE_H):m 2>>out.log
	@echo "\t\twrite FUSE_H in chip: finish"

fuse_l: 
	@echo "\t>>\twrite FUSE_L in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U lfuse:w:$(FUSE_L):m 2>>out.log
	@echo "\t\twrite FUSE_L in chip: finish"

fuse_x: 
	@echo "\t>>\twrite FUSE_X in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U xfuse:w:$(FUSE_X):m 2>>out.log
	@echo "\t\twrite FUSE_X in chip: finish"

read_fuse_h: 
	@echo "\t>>\twrite FUSE_H in chip: start"
	avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U hfuse:r:out.txt:h 2>>out.log
	@echo "\t\twrite FUSE_H in chip: finish"

read_fuse_l: 
	@echo "\t>>\twrite FUSE_L in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U lfuse:r:out.txt:h 2>>out.log
	@echo "\t\twrite FUSE_L in chip: finish"

read_fuse_x: 
	@echo "\t>>\twrite FUSE_X in chip: start"
	@avrdude -c $(PROGRAMMER) -p $(AVRDUDE_MCU) -P $(SERIAL_PORT)  \
		 -b $(SERIAL_BAUD)  -U xfuse:r:out.txt:h 2>>out.log
	@echo "\t\twrite FUSE_X in chip: finish"

clean:
	@echo "\t>>\tdelete all compiled files: start"
	@rm -f *.o
	@rm -f obj/*
	@rm -f out/*
	@echo "\t\tdelete all compiled files: finish"

#obj/core.ar: $(CORE_OBJ)
#	@echo "\t>>\tlink objects core: start"
#	@avr-ar rcs obj/core.ar $(CORE_OBJ) 2>>out.log
#	@echo "\t\tlink objects core: finish"

#COMPILE
#$(CORE_OBJ_CPP):
#	@echo "\t>>\tcompile cpp core: start"
#	@$(CCpp) $(CFLAGS_OBJ) -c $(CORE_CPP) 2>>out.log
#	@mv *.o $(DIR_OBJ) 
#	@echo "\t\tcompile cpp core: finish"
#out/main.elf: obj/src.ar obj/core.ar obj/lib.ar
#	@echo "\t>>\tlink all: start"
#	@$(CC) -g -mmcu=$(MCU) -o out/main.elf obj/src.ar obj/core.ar obj/lib.ar 2>>out.log
#	@echo "\t\tlink all: finish"


#$(CORE_OBJ_C):
#	@echo "\t>>\tcompile c core: start"
#	@$(CC) $(CFLAGS_OBJ) -c $(CORE_C) 2>>out.log
#	@mv *.o $(DIR_OBJ) 
#	@echo "\t\tcompile c core: finish"

