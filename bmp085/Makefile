##Makefile for bmp085 module
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi -lm

SRC = bmp085.c bmpmain.c
OBJ = $(SRC:.c=.o)
TARGET = -o bmpmain

all: bmpmain
bmpmain: $(OBJ)
	@echo "[Building]"
	@echo "Building bmpmain..."
	@$(CC) $(TARGET) $(OBJ) $(LIBS)
.c.o:
	@echo "Compiling $^"
	@$(CC) -c $(CFLAGS) -o $@ $^
clean:
	@echo "[Clean]"
	@rm -f bmpmain $(OBJ)
