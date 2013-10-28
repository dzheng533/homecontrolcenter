#ifndef _FORK_H
#define _FORK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PIDFILE "/var/run/hmcc.pid"

int init_daemon(void (*callBackHanle)());
void sig_term(int signo);

#endif