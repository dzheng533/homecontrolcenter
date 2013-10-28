#include "fork.h"
void (*callbackOnExit)(int code) = NULL;
void sig_term(int signo);

int init_daemon(void (*callBackHanle)(int code))
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
        //exit(0);
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
		     callbackOnExit = callBackHanle;
		 }
		 //handle signal
         signal(SIGTERM, &sig_term); /* arrange to catch the signal */
		 signal(SIGSTOP, &sig_term);
		 signal(SIGTSTP, &sig_term);
		 signal(SIGHUP,SIG_IGN);
    	 return 0;
    }
}

void sig_term(int signo){
    if(signo == SIGTERM){
    /* catched signal sent by kill(1) command */
	unlink(PIDFILE);
	(*callbackOnExit)(signo);
    exit(0);
  }else if(signo == SIGSTOP){
    (*callbackOnExit)(signo);
	exit(0);
  }else if(signo == SIGTSTP){
    (*callbackOnExit)(signo);
  }else{
    (*callbackOnExit)(signo);
  }
}

