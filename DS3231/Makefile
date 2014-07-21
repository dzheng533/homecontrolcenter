##Makefile for bmp085 module
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi -lm

SRC = ds3231main.c ds3231.c
OBJ = $(SRC:.c=.o)
TARGET = -o ds3231main

all: lcdmain
lcdmain: $(OBJ)
	@echo "[Building]"
	@echo "Building ds3231..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f ds3231main $(OBJ)
