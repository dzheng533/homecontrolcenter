##Makefile for bmp085 module
CC = gcc
INCLUDE = -I ../DS3231 -I../i2c1602
LIBS = -lwiringPi -lm

SRC = clock.c
OBJ = $(SRC:.c=.o) ../DS3231/ds3231.o ../i2c1602/lcd1602.o
TARGET = -o clock

all: clock
clock: $(OBJ)
	@echo "[Building]"
	@echo "Building clock..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS) $(INCLUDE)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f clock $(OBJ)
