#include "lcd1602.h"

int main(){
int i =0;
wiringPiSetup();
InitLCD();
/*
for(i=0;i<8;i++)
  pinMode(100+i,OUTPUT);

for(i =0 ;i<8;i++){
  printf("port:%d\r\n",i);
  digitalWrite(100+i,1);
  delay(2000);
  digitalWrite(100+i,0);
  delay(1000);
 
}*/
printf("LCD 1602 test.\r\n");
return 0;
}
