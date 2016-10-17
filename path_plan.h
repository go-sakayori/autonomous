#ifndef PATH_PLAN_H
#define PATH_PLAN_H

#include <math.h>
#include <stdio.h>
#include "grid_map.h"

#include <memory.h>

extern int PATH[100];

int get_goal(DEM *);

void pathplan(int,DEM *);

float calc_dist(int,int,DEM *);
float calc_elev(int,int,DEM *);
float calc_edge(int,int,DEM *);
float calc_cost(int, int, int, DEM *);
int sort_open(DEM *);

#endif
