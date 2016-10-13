#ifndef PATH_PLAN_H
#define PATH_PLAN_H
#include <math.h>

extern int PATH[100];
extern int Grid_Num;
extern float dem[][3];
int get_goal();

void pathplan(int);

float calc_dist(int,int);

float calc_elev(int,int);

float calc_cost(int,int);
#endif
