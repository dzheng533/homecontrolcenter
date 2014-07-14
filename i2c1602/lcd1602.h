#ifndef _LCDIIC1602_H
#define _LCDIIC1602_H

#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

#define ON 1
#define OFF 0

void LightSwitch(int flag);
void WriteLCDString(char *str);
void Position(int x, int y);

#endif
