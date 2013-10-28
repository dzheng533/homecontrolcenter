#include "fork.h"
void (*callbackOnExit)() = NULL;
void sig_term(int signo);

int init_daemon(void (*callBackHanle)())
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
		 //update callback handler
		 if(callBackHanle != NULL){
		     (*callBackHanle)();
		     callbackOnExit = callBackHanle;
		 }
		 //handle signal
		 openlog("daemontest", LOG_PID, LOG_USER);
         syslog(LOG_INFO, "program started.");
         signal(SIGTERM, &sig_term); /* arrange to catch the signal */
    	 return 0;
    }
}

void sig_term(int signo){
    if(signo == SIGTERM){
    /* catched signal sent by kill(1) command */
    syslog(LOG_INFO, "program terminated.");
    closelog();
	(*callbackOnExit)();
    unlink(PIDFILE);
    exit(0);
  }
}

