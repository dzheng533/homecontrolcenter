##Makefile for bmp085 module
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi -lm

SRC = lcd1602.c lcdmain.c
OBJ = $(SRC:.c=.o)
TARGET = -o lcdmain

all: lcdmain
lcdmain: $(OBJ)
	@echo "[Building]"
	@echo "Building lcdmain..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f lcdmain $(OBJ)
