
#include "log.h"
FILE *fp = NULL;

void logInfo(char* message){
    //check lock file
    if(access(LOGFILE,F_OK)==0 && access(LOGFILE,R_OK)==0){
    	fp = fopen(LOGFILE,"a+");
    	fgets(spid,10,fp);
    	printf("[INFO] %s.\n", message);
    	fclose(fp);
    	fp = NULL;
    }
}
void logError(char* message){
    //check lock file
    if(access(LOGFILE,F_OK)==0 && access(LOGFILE,R_OK)==0){
    	fp = fopen(LOGFILE,"a+");
    	fgets(spid,10,fp);
    	printf("[ERROR] %s.\n", message);
    	fclose(fp);
    	fp = NULL;
    }
}
void logDebug(char* message){
    //check lock file
    if(access(LOGFILE,F_OK)==0 && access(LOGFILE,R_OK)==0){
    	fp = fopen(LOGFILE,"a+");
    	fgets(spid,10,fp);
    	printf("[DEBUG] %s.\n", message);
    	fclose(fp);
    	fp = NULL;
    }
}

