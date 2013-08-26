
#ifndef _BMP085_H
#define _BMP085_H

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

//#define DEBUG_BMP085

int initBMP085(int pressureLevel);
int convertBMP085All();
void readBMP085(int *temp,int *pressure);
int calculateAltitude();
void testCaculation();
#endif
