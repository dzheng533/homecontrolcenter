##Makefile for bmp085 module
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi -lm

SRC = adc0832.c
OBJ = $(SRC:.c=.o)
TARGET = -o adc0832

all: adc0832
adc0832: $(OBJ)
	@echo "[Building]"
	@echo "Building adc0832..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f adc0832 $(OBJ)
