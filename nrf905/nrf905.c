#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define PIN_TRXCE 2 //GPIO2
#define PIN_AM    3 //GPIO3
#define PIN_TXEN  1 //GPIO1
#define PIN_PWR   4 //GPIO4
#define PIN_CO    5 //GPIO5
#define PIN_DR    6 //GPIO6

#define WC 0x00
#define RC 0x10
#define WTXBUF 0x20
#define RTXBUF 0x21
#define WTXADD 0x22
#define RTXADD 0x23
#define RRXBUF 0x24

//#define LOCADD    0xCC,0xCC,0xCC,0xCC
//#define REMOTEADD 0xCC,0xCC,0xCC,0xCE

#define LOCADD    0xCC,0xCC,0xCC,0xCE
#define REMOTEADD 0xCC,0xCC,0xCC,0xCC

#define DEVICEWORKMODE_STANDBY  0
#define DEVICEWORKMODE_RECEIVE  1
#define DEVICEWORKMODE_SEND     2

#define uchar unsigned char

uchar rfSConf[11] = {WC,
                  0x4c,0x08,  //430.0 MHz +6db
                  0x44,       //4 Bytes for TX and RX Address
                  0x20,0x20,  //32 Bytes for TX and RX buffer
                  LOCADD,     //Device Address
                  0x58};      //8bit CRC EN 16Mhz, no CLK output

uchar dataBuf[33] = {0x00};  //Data buffer 1 byte cmd, 32 bytes data
uchar txAdd[5] = {WTXADD,REMOTEADD};   //Address buffer

int writeCfg(uchar * rfCfg){
  int i,sizeReg = 0;
  sizeReg = sizeof(rfCfg);
  printf("Set Config:  ");
  printf("Size:%d\n",sizeReg);
  for(i=0;i<11;i++){
    printf("0x%02X ",rfCfg[i]);
  }
  printf ("\n");
  //Write config
  wiringPiSPIDataRW(0,rfSConf,11);
}


int initNRF905(){
  //initinal as receive device
  //Hardware init.
  pinMode(PIN_PWR,OUTPUT);
  pinMode(PIN_TXEN,OUTPUT);
  pinMode(PIN_TRXCE,OUTPUT);
  pinMode(PIN_CO,INPUT);
  pinMode(PIN_AM,INPUT);
  pinMode(PIN_DR,INPUT);
  //Power off mode
  digitalWrite(PIN_PWR,LOW);
  digitalWrite(PIN_TRXCE,LOW);
  digitalWrite(PIN_TXEN,LOW);
  // init config
  writeCfg(rfSConf);
}
int nrfMode(int mode){
  if(mode == DEVICEWORKMODE_RECEIVE){
    digitalWrite(PIN_PWR,HIGH);
    digitalWrite(PIN_TRXCE,HIGH);
    digitalWrite(PIN_TXEN,LOW);
    delay(1);
}else if(mode == DEVICEWORKMODE_SEND){
    digitalWrite(PIN_PWR,HIGH);
    digitalWrite(PIN_TRXCE,HIGH);
    digitalWrite(PIN_TXEN,HIGH);
  }else{
    //Standby Mode
    digitalWrite(PIN_PWR,HIGH);
    digitalWrite(PIN_TRXCE,LOW);
    digitalWrite(PIN_TXEN,LOW);
  }
}

int send(uchar * addr,uchar * data){
   //write remote address
   int i = 0;
   uchar txAddress[5] = {0x00};
   uchar txData[33] = {0x00};

   nrfMode(DEVICEWORKMODE_STANDBY);
   delay(1);
   printf("Address:");
   for(i = 0;i<5;i++){
      txAddress[i] = txAdd[i];
      //printf("0x%02x ",txAdd[i]);
   }
   for(i = 0;i<5;i++){
      printf("0x%02x ",txAddress[i]);
   }
   printf("\n");
   txData[0] = 0x20;

   txData[1] = 0x33;

   for(i=1;i<33;i++){
     txData[i] = data[i-1];
   }

   wiringPiSPIDataRW(0,txAddress,5);
   //write data to buffer
   printf("Data:");
   for(i=0;i<33;i++)
      printf("0x%02x ",txData[i]);
   printf("\n");
  // data
   wiringPiSPIDataRW(0,txData,33);
   //change device to send mode
   nrfMode(DEVICEWORKMODE_SEND);
   //while(digitalRead(PIN_DR)){
   //  delay(1);
   //}
   return 0;
}
int dataAvailable(){
   return digitalRead(PIN_DR);
}
int receive(uchar * data){
   int i = 0;
   uchar rxData[33] = {0x00};
   rxData[0] = RRXBUF;
   nrfMode(DEVICEWORKMODE_STANDBY);
   wiringPiSPIDataRW(0,rxData,33);
   nrfMode(DEVICEWORKMODE_RECEIVE);

   //printf("Receive Data:");
   for(i=0;i<33;i++){
     //printf("0x%02X ",data[i]);
     data[i] = rxData[i+1];
   }
   printf("\n");
   return 0;
}

int main(int argc,char **args){
  int i =0;
  int mode= 1; //receive 1, send 2
  int index = 1;
  //uchar rfSConf[11] = {WC,0x4c,0x04,0x44,0x20,0x20,DEVADD,0x58};
  uchar rfRConf[11] = {RC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  wiringPiSetup();
  if(wiringPiSPISetup(0,500000) == -1){
    printf("Could not initialise SPI.\n");
    return -1;
  }
  initNRF905();
  //writeCfg(rfSConf);
  //Write config
  //wiringPiSPIDataRW(0,rfSConf,11);

  //Read config
  wiringPiSPIDataRW(0,rfRConf,11);
  printf("Read Config: \n");
  for(i=0;i<11;i++){
    printf("0x%02X ",rfRConf[i]);
  }
  printf ("\n");
  if(argc>1){
    if(strcmp(args[1],"receive")==0){
      mode = 1;
      nrfMode(DEVICEWORKMODE_RECEIVE);
      printf("Receive Mode.\n");
    }else{
      mode = 2;
      printf("Send Mode.\n");
    }
  }else{
    printf("Usage: nrf905 <OPTION>\n OPTION: receive|send \n");
    return 0;
  }
  while(1){
    if(mode==1){
      if(dataAvailable()){
        receive(dataBuf);
        printf("Data Receive:{");
        //for(i=1;i<33;i++){
        //  printf("0x%02x ",dataBuf[i]);
        //}
        printf("%s",dataBuf);
        printf("}\n");
      }
    }else{
      sprintf(dataBuf,"Send Test:%d",index++);
      printf("Send:{%s},\n",dataBuf);
      send(txAdd,dataBuf);
      delay(1000);
    }
  }
  return 0;
}
