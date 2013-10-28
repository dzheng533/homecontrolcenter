#ifndef _LOG_H
#define _LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define LOGFILE "/var/log/hmcc.log"
void initLog();
void logInfo(char* message);
void logError(char* message);
void logDebug(char* message);

#endif
