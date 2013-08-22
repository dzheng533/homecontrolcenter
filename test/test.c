#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(){
  char ** deviceList;
  char *device;
  int i=0;
  int devCount = 20;
  int value = 0xF1;
  short AC1 = 0xF0;
  unsigned short MD1 = 0xF0;

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
//MD1 = value;
//AC1 = value;
  printf("%d MD1:%d-%02x AC1:%d-%02x\n",sizeof(short),MD1,MD1,AC1,AC1);
  free(device);
  free(deviceList);
  device = NULL;
  deviceList = NULL;
  return 0;
}
