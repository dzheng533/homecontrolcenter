/**
*  Define DS3231
*/
#ifndef DS3231_H

#define DS3231_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wiringPi.h>

#define DS3231ADDR 0x68
#define REG_SECOND 0x00
#define REG_MINUTE 0x01
#define REG_HOUR   0x02
#define REG_WEEK   0x03
#define REG_DATE   0x04
#define REG_MONTH  0x05
#define REG_YEAR   0x06

typedef struct {
  unsigned char year;
  unsigned char month;
  unsigned char day;
  unsigned char wday;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  unsigned char hmode;  //1 for 12, 0 for 24. default is 0
  unsigned char ampm;  //1 for pm ,0 for am.default is 0
} DSDateTime;

void initDS3231();
DSDateTime* readTime();
void writeTime(DSDateTime * dtime);

#endif
