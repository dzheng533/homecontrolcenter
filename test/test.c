#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(){
  char ** deviceList;
  char *device;
  int i=0;
  int devCount = 20;

 if(NULL !=  (deviceList =(char**)malloc(sizeof(char*)*devCount))){
  printf("Size:%d-%d-%d\n",sizeof(char*),sizeof(char),malloc_usable_size(deviceList));
 }else{
  printf("Memory.\n");
 }

  for(i=0;i<devCount;i++){
    if(NULL != (device = (char*)malloc(sizeof(char)*20))){
      sprintf(device,"String %d.\n",i);
      deviceList[i] = device;
    }else{
      printf ("Failed:%d.\n",i);
    }
  }

  for(i=0;i<devCount;i++){
    printf("String:%s\n",deviceList[i]);
  }

  free(device);
  free(deviceList);
  device = NULL;
  deviceList = NULL;
  return 0;
}
