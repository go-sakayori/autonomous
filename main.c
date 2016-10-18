#include "common.h"
#include "grid_map.h"
#include "path_plan.h"
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
  dem = (DEM*)malloc(sizeof(DEM) * 513);
  
  int i=0, point_num = 176656;
  int node_num;

  create_grid(point_num, dem, map);
  // printf("%d\n",Num_ex_dem);
 
  /*if(Num_ex_dem>300)
    Num_ex_dem = create_grid(Point_Num,dem_h_limit+0.1);
  if(Num_ex_dem>300){
    printf("can not traverse, back and rescan \n");
    exit(1);
    }*/
  //printf("%d\n",Num_ex_dem);

  Goal_ID = get_goal(dem);
  node_num = pathplan(Goal_ID,dem);  
  /*printf("\n passed node:%d\n",node_num);
  for(i=511;i>=0;i--)
    if(i % 32==0)
      printf("%d\n",(dem + i)->flag);
    else
      printf("%d",(dem + i)->flag);
  */

  //free memory
  free(dem);
  return 0;
}
