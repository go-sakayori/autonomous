#ifndef GRID_MAP_H
#define GRID_MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern float h_limit;
extern float lrf_heigt;
extern float vertex[][3];
extern float dem[][3];
extern float dist_limit;
extern int Ex_dem[512];
extern int Grid_Num;
int read_data();

int create_grid(int, float);

#endif
