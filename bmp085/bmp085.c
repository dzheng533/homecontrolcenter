#include "bmp085.h"
#include <math.h>

#define bmpAddress 0x77
#define bmpREGAC1  0xAA

#define bmpREGCMD  0xF4
#define bmpREGMSB  0xF6
#define bmpREGLSB  0xF7
#define bmpREGXLSB 0xF8

#define bmpCMDTEMP 0x2E
#define bmpCMDPRESS0 0x34
#define bmpCMDPRESS1 0x74
#define bmpCMDPRESS2 0xB4
#define bmpCMDPRESS3 0xF4

int fd = 0;
//Config
int osrs = 3;
int initialized = 0;

//Registers
short AC1,AC2,AC3 = 0x00;
unsigned short AC4,AC5,AC6 = 0x00;
short B1,B2,MB,MC,MD = 0x00;
long B3,B5,B6,B7 = 0;
unsigned long B4 = 0;

int UT,UP = 0;
int CT,CP=0;
//Privete functions

long calculateTemperature(){
  long X1,X2,T = 0;

  X1 = ((UT-AC6)*AC5) >> 15;
  X2 = (MC<<11)/(X1+MD);
  B5 = X1 + X2;
  printf("X1=%d,X2=%d,B5=%d.\n",X1,X2,B5);
  T = (B5+8) >> 4;
  #ifdef DEBUG_BMP085
  printf("UT:%d,Temperature:%d\n",UT,T);
  #endif
  return T;
}

int calculatePressure(){
  long X1,X2,X3,T,P = 0;
  #ifdef DEBUG_BMP085
  printf("B5:%d\n",B5);
  #endif
  B6 = B5 - 4000;
  #ifdef DEBUG_BMP085
  printf("B6:%d\n",B6);
  #endif
  X1 = (B2 * (B6 * B6 / (1 << 12))) / (1<<11);
  #ifdef DEBUG_BMP085
  printf("X1:%d\n",X1);
  #endif
  X2 = AC2 * B6 / (1 << 11);
  #ifdef DEBUG_BMP085
  printf("X2:%d\n",X2);
  #endif
  X3 = X1 + X2;
  #ifdef DEBUG_BMP085
  printf("X3:%d\n",X3);
  #endif
  B3 = (((AC1*4 + X3)<<osrs) + 2)/4;
  #ifdef DEBUG_BMP085
  printf("B3:%d\n",B3);
  #endif
  X1 = AC3 * B6 / (1 << 13);
  #ifdef DEBUG_BMP085
  printf("X1:%d\n",X1);
  #endif
  X2 = (B1 * (B6*B6/ (1 << 12))) /  (1 << 16);
  #ifdef DEBUG_BMP085
  printf("X2:%d\n",X2);
  #endif
  X3 = ((X1+X2)+2) / (1<<2);
  #ifdef DEBUG_BMP085
  printf("X3:%d\n",X3);
  #endif
  B4 = (AC4 * (unsigned long)(X3 + 32768)) >> 15;
  #ifdef DEBUG_BMP085
  printf("B4:%d\n",B4);
  #endif
  B7 = ((unsigned long)UP - B3)*(50000 >> osrs);
  #ifdef DEBUG_BMP085
  printf("B7:%d\n",B7);
  #endif
  if(B7< 0x80000000){
    P = (B7 * 2)/B4;
    //printf("1.P:%d",P);
  }else{
    P = (B7/B4) * 2;
    //printf("2.P:%d;",P);
  }
  #ifdef DEBUG_BMP085
  printf("P:%d\n",P);
  #endif
  X1 = (P  /(1<< 8)) * (P /(1<< 8));
  #ifdef DEBUG_BMP085
  printf("X1:%d\n",X1);
  #endif
  X1 = (X1 * 3038)/ (1<<16);
  #ifdef DEBUG_BMP085
  printf("X1:%d\n",X1);
  #endif
  X2 = (-7357 * P) /(1<<16);
  #ifdef DEBUG_BMP085
  printf("X2:%d\n",X2);
  #endif
  P = P + ((X1 + X2 + 3791)/(1<<4));
  #ifdef DEBUG_BMP085
  printf("P:%d\n",P);
  #endif
  #ifdef DEBUG_BMP085
  printf("CT:%d, Pressure:%d\n",CT,P);
  #endif
  return P;
}
int calculateAltitude(){
   int alititude = 0;
   double x, y ,z =0;
   double p,p0=0;
   p = (double)CP/100;
   p0 = 1013.25;
   x = p/p0;
   y = 1/5.255;
   z = pow(x,y);
   alititude = (int)(44330 * (1-z));
   return alititude;
}

int readPressure(){

  int MSB,LSB,XLSB = 0;
  int pressure = 0;
  if(fd>0){
    //write command
    wiringPiI2CWriteReg8(fd,bmpREGCMD, 0x34+(osrs<<6));
    //wait
    delay(100);
    MSB = wiringPiI2CReadReg8(fd, bmpREGMSB);
    LSB = wiringPiI2CReadReg8(fd, bmpREGLSB);
    XLSB = wiringPiI2CReadReg8(fd, bmpREGXLSB);
    pressure = ((MSB<<16)+(LSB<<8)+XLSB)>>(8-osrs);
    #ifdef DEBUG_BMP085
	printf("MSB=0x%02x,LSB=0x%02x,XLSB=0x%02x, Press:0x%02x\n",MSB,LSB,XLSB,pressure);
	#endif
  }
  UP = pressure;
  return pressure;
}
double readTemperature(){
  int MSB,LSB = 0;
  int temperature;
  if(fd>0){
    //write command
    wiringPiI2CWriteReg8(fd,bmpREGCMD,bmpCMDTEMP);
    //wait
    delay(10);
    MSB = wiringPiI2CReadReg8(fd,bmpREGMSB);
    LSB = wiringPiI2CReadReg8(fd,bmpREGLSB);
    temperature = (MSB<<8)+(LSB);
	#ifdef DEBUG_BMP085
    printf("MSB=0x%02x,LSB=0x%02x, Temperature:0x%02x\n",MSB,LSB,temperature);
	#endif
  }
  UT = temperature;
  return temperature;
}

//Public functions

int initBMP085(int pressureLevel){
   int i = 0;
   int regAdd = 0xAA;
   int regValue = 0;
   if(pressureLevel >=0 && pressureLevel <=3){
      osrs = pressureLevel;
   }else{
      osrs = 3;
   }

   fd = wiringPiI2CSetup(bmpAddress);
   if(fd > 0){
     regAdd = 0xAA;
	 for( i=0;i<11;i++){
       regValue = wiringPiI2CReadReg8(fd,regAdd++) << 8;
	   regValue += wiringPiI2CReadReg8(fd,regAdd++);
       #ifdef DEBUG_BMP085
	   //printf("%d=%d\n",i,regValue);
	   #endif
	   if(regAdd-2 == 0xAA)
	     AC1 = regValue;
       else if(regAdd-2 == 0xAC)
	     AC2 = regValue;
	   else if(regAdd-2 == 0xAE)
	     AC3 = regValue;
	   else if(regAdd-2 == 0xB0)
	     AC4 = regValue;
	   else if(regAdd-2 == 0xB2)
	     AC5 = regValue;
	   else if(regAdd-2 == 0xB4)
	     AC6 = regValue;
	   else if(regAdd-2 == 0xB6)
	     B1 = regValue;
	   else if(regAdd-2 == 0xB8)
	     B2 = regValue;
	   else if(regAdd-2 == 0xBA)
	     MB = regValue;
	   else if(regAdd-2 == 0xBC)
	     MC = regValue;
	   else if(regAdd-2 == 0xBE)
	     MD = regValue;
     }
   }

   initialized = 1;
   return fd;
}

int convertBMP085All(){
  if(initialized == 0)
    return -1;
  //Start convert process
  readTemperature();
  readPressure();
  CT = calculateTemperature();
  CP = calculatePressure();
}

void readBMP085(int *temp,int *pressure){
   *temp = CT;
   *pressure = CP;
}

void testCaculation(){
AC1 = 408;
AC2 = -72;
AC3 = -14383;
AC4 = 32741;
AC5 = 32757;
AC6 = 23153;
B1 = 6190;
B2 = 4;
MB = 32768;
MC = -8711;
MD = 2868;
UT = 27898;
UP = 23843;
osrs = 0;
  CT = calculateTemperature();
  CP = calculatePressure();
  printf("Temperature:%d\n",CT);
  printf("Pressure:%d\n",CP);
}
