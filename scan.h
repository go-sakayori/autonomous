#ifndef SCAN_H
#define SCAN_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>         // for read, write, close 
#include <sys/types.h>      // for open 
#include <sys/stat.h>       // for open
#include <fcntl.h>          // for open
#include <sys/ioctl.h>      // for ioctl

#include "driver/urbtc.h"
#include "driver/urobotc.h"


void scan_terrain();

struct ccmd iXs_init_data();
struct uout gain_init_data();
#endif
