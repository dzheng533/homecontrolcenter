#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define IRPORT 6

void receive(){
   int pulse = 0;
   int space = 0;
    while(1){
      if(digitalRead(IRPORT)){
         pulse++;
      }else{
         space++;
      }
      if(pulse == 1 && space >0){
        printf("space : %d\n",space);
        space = 0;
      }else if(space == 1 && pulse > 0){
        printf("pulse : %d\n",pulse);
        pulse = 0;
      }
      delayMicroseconds(1);//      delay(1);
      if(pulse >20000)
         break;
    }

}

int main(int argc, char **args){
   int pid =0;
   int sign = 0;
   int lastsign =0;
   int count = 0;
   pid = getpid();
   printf("IRC detect starting. pid:%d.\n",pid);
   if(wiringPiSetup() == -1)
      return 0;
   pinMode(IRPORT,INPUT);
   while(1){
      sign = digitalRead(IRPORT);
      if(lastsign==sign){
         //count>0?printf("\nCount:%d\n",count):"";
         //count =0;
         continue;
      }

      if(sign){
         printf("--");
      }else{
         printf("__");
      }
      count++;
      lastsign = sign;
      delayMicroseconds(1);
 /* 
     if(lastsign && !sign){
         printf("Start Receive.\n");
         receive();
         printf("End Receive.\n");
      }
      delay(100);
*/
   }
}
