#Makefile for nrf905
CC = gcc

all: nrf905
nrf905:nrf905.o
	$(CC) -o nrf905 nrf905.o -lwiringPi
clean:
	$(RM) *.o nrf905
