
#include "log.h"

FILE *fp = NULL;
char tmpbuf[20];
void locTime(){
    time_t t;
	struct tm *newtime;
	t = time(NULL);
	newtime=localtime(&t);
	strftime(tmpbuf, 20, "%F %T", newtime);
}
void logInfo(char* message){
    fp = fopen(LOGFILE,"a+");
	if(fp != NULL){
    	locTime();
    	fprintf(fp,"[INFO] %s - %s\n",tmpbuf , message);
    	fclose(fp);
    	fp = NULL;
    }
}
void logError(char* message){
    fp = fopen(LOGFILE,"a+");
	if(fp != NULL){
    	locTime();
    	fprintf(fp,"[ERROR] %s - %s\n", tmpbuf, message);
    	fclose(fp);
    	fp = NULL;
    }
}
void logDebug(char* message){
    fp = fopen(LOGFILE,"a+");
    if(fp != NULL){
    	locTime();
	    fprintf(fp,"[DEBUG] %s - %s\n", tmpbuf, message);
    	fclose(fp);
    	fp = NULL;
   }
}

