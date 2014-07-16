#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <wiringPi.h>

#define DS3231ADDR 0x68
#define REG_SECOND 0x00
#define REG_MINUTE 0x01
#define REG_HOUR   0x02
#define REG_WEEK   0x03
#define REG_DATE   0x04
#define REG_MONTH  0x05
#define REG_YEAR   0x06

int fd = 0;
struct tm Date;
int main(int argc, char const *argv[])
{
	char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    struct tm *hwClock;
    time(&timep);
    p = gmtime(&timep);
    printf("System: %d-%d-%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);

    hwClock = (struct tm)* malloc(sizeof(struct tm));
	fd = wiringPiI2CSetup(DS3231ADDR);
	if(fd >0){
       hwClock->tm_second = wiringPiI2CReadReg8(fd,REG_SECOND);

	}*/

    free(hwClock);
	return 0;
}
