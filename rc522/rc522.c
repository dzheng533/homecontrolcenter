#include "../common.h"
#include <wiringPiSPI.h>
#define CMDREGADD 0x01
#define uchar unsigned char
unsigned char cmdReg[2] = {0x01,0x2C};

uchar readRc522Reg(uchar cmd){
    uchar cmdREG = cmd;
    wiringPiSPIDataRW(0,&cmdREG,1);
    return cmdREG;
}

void writeRc522Reg(uchar cmd,uchar value){
    uchar cmds[2]= {0x00,0x00};
    cmds[0] = cmd;
    cmds[1] = value;
    wiringPiSPIDataRW(0,cmds,2);
}

int main(){
   if( wiringPiSetup() < 0 ){
     return -1;
   }
   if( wiringPiSPISetup(0,500000) < 0 ){
     return -2;
   }
   printf("Commang REG:");
   //wiringPiSPIDataRW(0, cmdReg,1);
   printf("R:0x%02x; ",readRc522Reg(CMDREGADD));
   printf("BW:0x%02x; ",cmdReg[1]);
   //cmdReg[0] = 0x01;
   //wiringPiSPIDataRW(0, cmdReg,2);
   writeRc522Reg(CMDREGADD,0x20);
   //printf("AW:0x%02x; \n",cmdReg[0]);

   printf("Final:0x%02x,0x%02x",cmdReg[0],cmdReg[1]);
   printf("\n");
}

