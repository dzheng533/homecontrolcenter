#include "lcd1602.h"

int main(){
int i =0;
wiringPiSetup();
InitLCD();
WriteLCDString("LCD 1602 test.");
printf("LCD 1602 test.\r\n");
return 0;
}
