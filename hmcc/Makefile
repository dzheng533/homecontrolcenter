##Makefile for hmcc application
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi -lm

SRC = bmp085.c fork.c log.c main.c
OBJ = $(SRC:.c=.o)
TARGET = -o hmcc

all: hmcc
hmcc: $(OBJ)
	@echo "[Building]"
	@echo "Building hmcc..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f hmcc $(OBJ)
