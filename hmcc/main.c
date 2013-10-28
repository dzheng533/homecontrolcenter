
#include "bmp085.h"
#include "fork.h"
#include "log.h"
#include "w1temp.h"
#include "dbsqlite3.h"

#define VERSION 1.0.0

char ** deviceList = NULL;
int deviceCount = 0;

  
void onExit(int code){
   //char strBuffer[100] = {'\0'};
	  
  if(code == SIGTERM){
    //sprintf(strBuffer,"App Closed.Code:%s=%d","SIGTERM",code);
    logInfo("App Close,SIGTERM");
    exit(0);
  }else if(code == SIGSTOP){
    //sprintf(strBuffer,"App Closed.Code:%s=%d","SIGSTOP",code);
   logInfo("App Close,SIGSTOP");
	exit(0);
  }else if(code == SIGTSTP){
    //sprintf(strBuffer,"App Closed.Code:%s=%d","SIGTSTP",code);
   logInfo("App Close,SIGTSTP");
  }
  logInfo("App Close.");
   
   
   //free(strBuffer);
}

void readw1Temperature(){
  int i = 0;
  double douTemperature = 0.0;
  char *strBuffer = NULL;
  
  if(NULL == (strBuffer = (char*)malloc(sizeof(char)*1024)))
      return;
  if(NULL ==  (deviceList =(char**)malloc(sizeof(char*)*MAXW1DEVICE))){
     return;
  }else{
     deviceCount = w1DeviceList(deviceList);
	 sprintf(strBuffer,"Temperature Device:%d",deviceCount);
     logInfo(strBuffer);
	 *strBuffer = '\0';
     
     for(i=0;i<deviceCount;i++){
          douTemperature = readTemperature(deviceList[i]);
          sprintf(strBuffer,"Device ID:%s-%f",deviceList[i],douTemperature);
		  logInfo(strBuffer);
          insertTemperature(douTemperature);
     }
	 free(strBuffer);
	 free(deviceList);
	 strBuffer = NULL;
     deviceList = NULL;
  } 
}
int main(int argc,char** args){
/*	
  pid_t pid = 0;
  char * strBuffer = NULL;

  if(NULL == (strBuffer = (char*)malloc(sizeof(char)*1024)))
      return;
  
  pid = getpid();
  sprintf(strBuffer,"start pid:%d",pid);
  logInfo(strBuffer);
*/

  logInfo("App Start.");
  if(argc >1){
    if(strcmp(args[1],"daemon") == 0){
      if(init_daemon(&onExit)){
        exit(-1);
      }
      logInfo("App daemon thread start");
	}else{
	   //Start as normal app
	   logInfo("App normal thread start");
	}
  }
/*
  pid = getpid();
  sprintf(strBuffer," while pid:%d",pid);
  free(strBuffer);
  */
  while(1){
      readw1Temperature();
      //logInfo(strBuffer);
	  sleep(300); //sleep 5 mintues
  }

}
