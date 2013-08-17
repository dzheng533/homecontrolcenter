#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "w1temp.h"
#include "dbsqlite3.h"

int main(){
  char ** deviceList = NULL;
  int deviceCount = 0;
  int i = 0;
  double douTemperature = 0.0;
  struct sysinfo *info = NULL;
  
  //FILE *fp = NULL;
  info = (struct sysinfo *)malloc(sizeof(struct sysinfo));
  if(NULL ==  (deviceList =(char**)malloc(sizeof(char*)*MAXW1DEVICE))){
     return 0;
  }else{
     deviceCount = w1DeviceList(deviceList);
     printf("Device:%d.\n",deviceCount);
     while(1){
       //fp = fopen("./temp.log","a+");
       for(i=0;i<deviceCount;i++){
          douTemperature = readTemperature(deviceList[i]);
          printf("Device ID:%s-%f\n",deviceList[i],douTemperature);
          insertTemperature(douTemperature);
       }
       printf("------------\n");
/*
       sysinfo(info);
       printf("System Uptime:%d\n",info->uptime);
       printf("System Overload 1 min:%d\n",info->loads[0]);
       printf("System Overload 5 mins:%d\n",info->loads[1]);
       printf("System Overload 15 mins:%d\n",info->loads[2]);
       printf("System Total Ram:%d\n",info->totalram);
       printf("System Free Ram:%d\n",info->freeram);
*/       
       sleep(60);
     }
     printf("----END----\n");
     free(info);
     free(deviceList);
     info = NULL;
     deviceList = NULL;

  }
  return 0;
}