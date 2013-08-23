
#include "bmp085.h"
#define PRESSLEVEL 3

int main(){
int temperature,pressure,alititude = 0;
 if(!initBMP085(PRESSLEVEL)){
   printf("error.");
 }
 convertBMP085All();
 readBMP085(&temperature,&pressure);
 alititude = calculateAltitude();
 printf("BMP085 Temperture: %1f ℃,Pressure:%d par,Alititude:%d\n",(double)temperature/10,pressure,alititude);
// testCaculation();
 return 0;
}
