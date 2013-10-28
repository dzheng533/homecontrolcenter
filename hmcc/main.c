
#include "bmp085.h"
#include "fork.h"
#include "log.h"

#define VERSION 1.0.0

void onExit(){
   logInfo("App Exit.");
}
int main(int argc,char** args){
  
  logInfo("App Start.");
  if(argc >1){
    if(strcmp(args[1],"daemon") == 0){
      if(init_daemon(&onExit)){
        exit(-1);
      }
      logInfo("App daemon thread start.");
	}else{
	   //Start as normal app
	   logInfo("App normal thread start.");
	}
  }
  while(1){
      
      sleep(10000);
  }
}
