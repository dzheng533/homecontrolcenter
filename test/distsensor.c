#include <stdio.h>
#include <wiringPi.h>
#include <sys/wait.h>

int main(){
  int inear = 0;
  if(wiringPiSetup()==-1){
    return(-1);
  }
  pinMode(1,INPUT);
  pinMode(2,OUTPUT);

  while(1){
    inear = digitalRead(1);
    //printf("Near:%d\n",inear);
    if(inear == LOW){
      digitalWrite(2,HIGH);
    }else{
      digitalWrite(2,LOW);
    }
    delay(100);
  }
}
