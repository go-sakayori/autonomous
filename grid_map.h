#ifndef GRID_MAP_H
#define GRID_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INTERVAL 0.50
#define GRID_NUM 512
#define H_LIMIT 1
#define DEM_H 0.1

typedef struct{
  float x;
  float y;
  float z;
  bool flag; //false for danger
} DEM;

extern float h_limit;
extern float lrf_heigt;
extern float vertex[][3];
extern float dist_limit;
extern int Ex_dem[512];
extern int Grid_Num;
int read_data();

int create_grid(int, DEM *);

#endif
