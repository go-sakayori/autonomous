#include "common.h"
#include "grid_map.h"
#include "path_plan.h"
#include "scan.h"
#include <stdio.h>
#include <stdlib.h>

int main(){



  //set up map information
  Map map; 
  map.size = 8.0;
  map.interval = 0.5;
  map.row = map.size / map.interval;
  map.column = 2 * map.row;
  map.point = map.row * map.column;
  map.threshold = 1.0;

  //memory allocation for dem data
  DEM *dem;
  dem = (DEM*)malloc(sizeof(DEM) * (map.point + 1)); //+1 add start node
  
  int i, point_num = 176656;
  int node_num;

  create_grid(point_num, dem, map);

  //path planning
  Goal_ID = get_goal(dem);
  node_num = pathplan(Goal_ID, dem, map);  
  //printf("\n passed node:%d\n",node_num);
  /*for(i=511;i>=0;i--)
    if(i % 32==0)
      printf("%d\n",(dem + i)->flag);
    else
      printf("%d",(dem + i)->flag);
  */

  //create motion table
  int *motion;
  motion = (int*)malloc(sizeof(int) * node_num);
  create_motion(Goal_ID, dem, motion, node_num, map.column);

  //for(i=0; i<node_num; i++)
  //  printf("%d\n",motion[i]);

  //free memory
  free(dem);

  return 0;
}
