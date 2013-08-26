#include "../common.h"
#include <wiringPiSPI.h>
#define CMDREGADD 0x01
unsigned char cmdReg[2] = {0x01,0x2C};

int main(){
   if( wiringPiSetup() < 0 ){
     return -1;
   }
   if( wiringPiSPISetup(0,500000) < 0 ){
     return -2;
   }
   printf("Commang REG:");
   printf("W:0x%02x; ",cmdReg[1]);
   wiringPiSPIDataRW(0, cmdReg,2);
   printf("AW:0x%02x; ",cmdReg[0]);
   wiringPiSPIDataRW(0, cmdReg,1);
   printf("R:0x%02x; ",cmdReg[0]);

   printf("Final:0x%02x,0x%02x",cmdReg[0],cmdReg[1]);
   printf("\n");
}

