#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define WC 0x00
#define RC 0x10
#define WTXBUF 0x20
#define RTXBUF 0x21
#define WTXADD 0x22
#define RTXADD 0x23
#define RRXBUF 0x24

#define DEVADD 0xCC,0xCC,0xCC,0xCC

#define uchar unsigned char
//uchar rfConf[11] = {0x21,0x6c,0x00,0x44,0x20,0x20,0xe7,0xe7,0xe7,0xe7,0xe7};

//read
//uchar rfConf[11] = {0x10,0x4c,0x0c,0x44,0x04,0x04,0xcc,0xcc,0xcc,0xcc,0x58};
int main(){
  int i =0;

  uchar rfSConf[11] = {WC,0x4c,0x04,0x44,0x20,0x20,DEVADD,0x58};
  uchar rfRConf[11] = {RC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  uchar rxBuf[33] = {0x00};
  uchar txAdd[5] = {0x00};

  printf("Set Config:  ");
  for(i=0;i<11;i++){
    printf("0x%lX ",rfSConf[i]);
  }
  printf ("\n");
  
  wiringPiSetup();
  if(wiringPiSPISetup(0,500000) == -1){
  	printf("Could not initialise SPI.\n");
    return -1;
  }
 
  //Write config
  //wiringPiSPIDataRW(0,rfSConf,11);
  
  //Read config
  wiringPiSPIDataRW(0,rfRConf,11);
  printf("Read Config: ");
  for(i=0;i<11;i++){
    printf("0x%X ",rfRConf[i]);
  }
  printf ("\n");
  return 0;
}
