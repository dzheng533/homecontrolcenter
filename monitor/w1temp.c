#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "w1temp.h"

char * trim(char *str);

int w1DeviceList(char **deviceList){
   int iDevCount = 0;
   FILE *fp = NULL;
   char *deviceID = NULL;
   if(NULL == deviceList){
   	 return -2;
   }
   if(access(W1DEVICESLIST,F_OK) ==0 && access(W1DEVICESLIST,R_OK) == 0){
   		fp = fopen(W1DEVICESLIST,"r");
   		if(NULL==fp){
   		  //open file error
   		  printf("Error Code: %d\n",errno);
   		  return -1;
   		}
   		while(!feof(fp)){
   			if(NULL != (deviceID = (char*)malloc(sizeof(char)*IDLEN))){
   			  fgets(deviceID,IDLEN,fp);
   			 	trim(deviceID);
   			 	if(strlen(deviceID)>0){
   			    if(iDevCount < MAXW1DEVICE){
   			      deviceList[iDevCount++] = deviceID;
   			    }else{
   			  
   			    }
   			  }
   		  }else{
   		  	
   		  }
   		  
   		}
   }else{
     //can't find W1 Device.
   }
   
   if(NULL != deviceID){
     free(deviceID);
     deviceID = NULL;	
   }
   if(NULL != fp){
   	fclose(fp);
   	fp = NULL;
  }
  
  return iDevCount;
}
double readTemperature(char *deviceID){
	char* tempFile = NULL;
	char* tempContent = NULL;
	char* strTemperature = NULL;
	int filePathLen = 0;
	int ipos = 0;
  double douTemperature = 0.0;
  
	FILE *fp = NULL;
	filePathLen = strlen(W1DEVICEBASE)+strlen(W1SLAVE)+strlen(deviceID)+1;
	//printf("PathSize:%d\t",filePathLen);
	if(NULL != (tempFile = (char*)malloc(sizeof(char)*(filePathLen)))){
		*tempFile='\0';
    strcat(tempFile,W1DEVICEBASE);
    strcat(tempFile,deviceID);
    strcat(tempFile,W1SLAVE);
    //printf("%s\n",tempFile);
	  
	  fp = fopen(tempFile,"r");
   		if(NULL==fp){
   		  //open file error
   		  printf("Error Code: %d\n",errno);
   		  return -1;
   		}
   		if(NULL != (tempContent = (char*)malloc(sizeof(char)*1024))){
   		   while(!feof(fp)){
   		    fgets(tempContent,1024,fp);
   		 	  trim(tempContent);
   		 	  ipos = strcspn(tempContent,"t=");
   		 	  
   		 	  if(ipos>0 && tempContent[ipos]=='t' && tempContent[ipos+1]=='='){
   		 	  	strTemperature = tempContent+ipos+2;
   		 	  	douTemperature = atof(strTemperature)/1000;
   		 	  }
   		 	  *tempContent='\0';
   		   }
   		}
   		
	  if(NULL != fp){
   	  fclose(fp);
   	  fp = NULL;
    }
	}else{
	
	}
	
	free(tempContent);
	free(tempFile);
	tempFile = NULL;
	tempContent = NULL;
  return douTemperature;	
}

char * trim(char *str)
{
    char *str_last,*str_cur;
    if(str==NULL)
        return NULL;
    for(;*str==0x20 || *str=='\t'; ++str);
    for(str_last=str_cur=str;*str_cur!='\0';++str_cur)
        if(*str_cur!=0x20&&*str_cur!='\t'&&*str_cur!='\n')
            str_last=str_cur;
    *++str_last=0;
    return str;
}