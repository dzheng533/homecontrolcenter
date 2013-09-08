#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PIDFILE "/var/run/daemon-test.pid"

int init_daemon()
{
    FILE *fp = NULL;
    pid_t fid;
    pid_t pid;
    int i,fd;
    char spid[10] = {'\0'};

    //check lock file
    if(access(PIDFILE,F_OK)==0 && access(PIDFILE,R_OK)==0){
    	fp = fopen(PIDFILE,"rb+");
    	fgets(spid,10,fp);
    	printf("Daemon Thread has been started.pid:%s.\n",spid);
    	fclose(fp);
    		return(-1);
    }

    fid = fork();
    if(fid < 0){ //
        printf("Fork Error!");
        return(-2);
    }
    else if (fid > 0 ) {
        //printf("Father process exited!\n"); 
        return(-3);
    }else{
    	 setsid();
		   for (i = 0;i < getdtablesize();i++){
		     close(i);
		   }
		   chdir("/");
		   umask(0);
    	 pid = getpid();
    	 //Set lock file
    	 fp = fopen(PIDFILE,"w+");
    	 fprintf(fp,"%d",pid);
    	 fclose(fp);
    	 fp = NULL;
    	 return 0;
    }
}

void sig_term(int signo){
    if(signo == SIGTERM){
    /* catched signal sent by kill(1) command */
    syslog(LOG_INFO, "program terminated.");
    closelog();
    unlink(PIDFILE);
    exit(0);
  }
}

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
