#ifndef _H_SQLITE3
#define _H_SQLITE3
#include <sqlite3.h>
#define SQL_OK 0
#define SQL_ERR -1

#define SQL_INSTEMPERATURE "insert into TEMPERATURE(TEMP_LOC,TEMP_TEMPERATURE,TEMP_TIMESTAMP) values ('%s','%s',%d)"
//#define DB_FILE "/root/projects/hcc/hmcc/monitor.db"
#define DB_FILE "/root/wwwroot/db/monitor.db"

char** getDeviceList();
int insertTemperature(double temperature);
#endif  /* ifndef */
