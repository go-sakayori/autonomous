#ifndef GRID_MAP_H
#define GRID_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEM_H 0.3

typedef struct{
  float size; // x[m] * 2x [m] retangle
  float interval; //interval between each point
  int row;
  int column;
  int point; //number of point(node) in map
  float threshold;
} Map;


typedef struct{
  float x;
  float y;
  float z;
  int flag; //obstacle 0, traverse 1, right 2, left 3, bottom 4, top 5
  int status; //0 for close, 1 for open, 2 for unopened 
  float cost;
  int prev;
} DEM;

extern float h_limit;
extern float lrf_heigt;
extern float dist_limit;
extern int Ex_dem[512];

void create_grid(int, DEM *, Map);

#endif
