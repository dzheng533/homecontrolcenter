
#include "bmp085.h"
#define PRESSLEVEL 3

int main(){
int temperature,pressure = 0;
 if(!initBMP085(PRESSLEVEL)){
   printf("error.");
 } 
 convertBMP085All();
 readBMP085(&temperature,&pressure);
 printf("BMP085 Temperture: %1f ℃,Pressure:%d par\n",(double)temperature/10,pressure);
 return 0;
}
