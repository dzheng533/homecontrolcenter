#ifndef _H_W1
#define _H_W1
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>

#define W1DEVICESLIST "/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves"
#define W1DEVICEBASE "/sys/bus/w1/devices/"
#define W1SLAVE "/w1_slave"

#define MAXW1DEVICE 20
#define IDLEN 20

int w1DeviceList(char **deviceList);
double readTemperature(char *deviceID);

#endif