LIB: -lwiringPi

all: monitor

monitor:
    gcc -O2 monitor.c w1temp.c -lwiringPi
test:
    gcc -O2  maintest.c w1temp.c -lwiringPi
clean:
    rm *.o
