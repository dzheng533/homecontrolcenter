
#include "bmp085.h"
#include "fork.h"

int main(int argc,char** args){

  if(argc >1){
    if(args[1]
  }
  if(init_daemon()){
    exit(-1);
  }

  openlog("daemontest", LOG_PID, LOG_USER);
  syslog(LOG_INFO, "program started.");
  signal(SIGTERM, sig_term); /* arrange to catch the signal */

  while(1){
     sleep(10);
  }
}