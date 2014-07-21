#include <ds3231.h>
#include <lcd1602.h>

main(){
  DSDateTime *dt;
  char strDate[16];
  char strTime[16];
  wiringPiSetup();
  initDS3231();
  InitLCD();
  while(1){
  dt = readTime();
  sprintf(strDate,"Date:20%d-%02d-%02d",dt->year,dt->month,dt->day);
  sprintf(strTime,"Time:%02d:%02d:%02d",dt->hour,dt->minute,dt->second);
  printf("%s %s\r\n",strDate, strTime);
  Position(0,0);
  WriteLCDString(strDate);
  Position(0,1);
  WriteLCDString(strTime);
  delay(1000);
  }
}
