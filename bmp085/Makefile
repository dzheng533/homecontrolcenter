##Makefile for bmp085 module
CC = gcc
INCLUDE = -I
LIBS = -lwiringPi

SRC = bmp085.c bmpmain.c

OBJ = $(SRC:.c=.o)

all: bmpmain

bmpmain: $(OBJ)
 @$(CC) $(OBJ) $(LIBS)
