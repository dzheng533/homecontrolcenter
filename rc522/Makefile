#Makefile for nrf905
CC = gcc

all: rc522
rc522:rc522.o
	$(CC) -o rc522 rc522.o -lwiringPi
clean:
	$(RM) *.o rc522
