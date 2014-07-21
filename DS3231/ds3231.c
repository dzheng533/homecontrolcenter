#include "ds3231.h"

int fd = 0;

unsigned char BCDENCODE(unsigned char value){
 unsigned char bcdval ,i,j = 0;
 i = value / 10;
 j = value % 10;
 bcdval = j + (i<<4);
 return bcdval;
}
unsigned char BCDDECODE(unsigned char bcd){
  unsigned char val=0;
  val = (bcd>>4)*10 + (bcd & 0x0F);
  return val;
}
void initDS3231(){
  fd = wiringPiI2CSetup(DS3231ADDR);
  if(fd==-1){
    printf("DS3231 init error.");
    return;
  }
  
}

DSDateTime* readTime(){

  DSDateTime* dtime = (DSDateTime *)malloc(sizeof(DSDateTime));
  unsigned char tmpSec = 0;
  unsigned char tmpMin = 0;
  unsigned char tmpHour = 0;
  unsigned char tmpDay = 0;
  unsigned char tmpMonth = 0;
  unsigned char tmpYear = 0;
  tmpSec = wiringPiI2CReadReg8(fd,REG_SECOND);
  tmpMin = wiringPiI2CReadReg8(fd,REG_MINUTE);
  tmpHour = wiringPiI2CReadReg8(fd,REG_HOUR);
  dtime->second = BCDDECODE(tmpSec);
  dtime->minute = BCDDECODE(tmpMin);
  if((tmpHour&0x40)){
      dtime->hour = ((tmpHour&0x10)>>4)*10 + (tmpHour & 0x0F);
  }else{
      dtime->hour = ((tmpHour&0x30)>>4)*10 + (tmpHour & 0x0F);
  }

  dtime->wday = wiringPiI2CReadReg8(fd,REG_WEEK);
  tmpDay = wiringPiI2CReadReg8(fd,REG_DATE);
  tmpMonth = wiringPiI2CReadReg8(fd,REG_MONTH);
  tmpYear = wiringPiI2CReadReg8(fd,REG_YEAR);

  dtime->day = BCDDECODE(tmpDay);
  dtime->month  = ((tmpMonth&0x01)>>4) *10 + (tmpMonth & 0x0F);
  dtime->year = BCDDECODE(tmpYear);
  return dtime;
}

void writeTime(DSDateTime* dTime){
       //wiringPiI2CWriteReg8(fd,REG_YEAR,BTOBCD(14));
       /*wiringPiI2CWriteReg8(fd,REG_MONTH,0x07);
       wiringPiI2CWriteReg8(fd,REG_DATE,0x17);
       wiringPiI2CWriteReg8(fd,REG_WEEK,4);
       wiringPiI2CWriteReg8(fd,REG_HOUR,0x01);
       wiringPiI2CWriteReg8(fd,REG_MINUTE,0x05);
       wiringPiI2CWriteReg8(fd,REG_SECOND,0x30);
      */
}
