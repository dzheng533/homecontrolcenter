#include "dbsqlite3.h"
#include <stdio.h>
#include <time.h>
#include <malloc.h>
char **getDeviceList(){/*
	int rs = 0;
	sqlite3 *db;
	sqlite3_stmt *stmt = NULL;
	char * strErr = NULL;
	char * strSql = NULL;
	char * strSqlTail = NULL
	time_t timep;
	char *sql = "select * from Location";
	rs = sqlite3_open_v2(DB_FILE,&db);
	sqlite3_prepare_v2(db,sql,strlen(sql),stmt,&strSqlTail);
	
	if(rs != SQLITE_OK){
	  printf("SQL Error:%s\n",strErr);
	}
	if(strErr != NULL){
		sqlite3_free(strErr);
	}
	if(strSql != NULL)
		free(strSql);
	sqlite3_close(db);*/
	return NULL;
}
int insertTemperature(double temperature){
	int rs = 0;
	sqlite3 *db;
	char * strErr = NULL;
	char * strSql = NULL;
	char * strTemp = NULL;
	time_t timep;
	rs = sqlite3_open(DB_FILE,&db);
	if(rs){
		 printf("Can't open database:%s\n",sqlite3_errmsg(db));
     sqlite3_close(db);		 
	   return SQL_ERR;
	}
	
  time(&timep);
  //printf("%s",asctime(gmtime(&timep)));
  strSql = (char *)malloc(1024);
  strTemp = (char *)malloc(1024);
	sprintf(strSql,"insert into TEMPERATURE(TEMP_LOC,TEMP_TEMPERATURE,TEMP_TIMESTAMP) values ('%s',%f,%d)","TEST",temperature,timep);
	logDebug(strSql);
	rs = sqlite3_exec(db,strSql,NULL,NULL,&strErr);
	if(rs != SQLITE_OK){
	  sprintf(strTemp,"SQL Error: %s.\n",strErr);
	  logError(strTemp);
	}
	if(strErr != NULL){
		sqlite3_free(strErr);
	}
	if(strSql != NULL)
		free(strSql);
	sqlite3_close(db);
	
}