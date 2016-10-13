#include "common.h"
#include "grid_map.h"
#include "path_plan.h"
#include <stdio.h>

int main(){
  
 
  
  Point_Num = read_data();
  printf("Point Num? %d\n",Point_Num);
  Num_ex_dem = create_grid(Point_Num,dem_h_limit);
  printf("%d\n",Num_ex_dem);
 
  if(Num_ex_dem>300)
    Num_ex_dem = create_grid(Point_Num,dem_h_limit+0.1);
  if(Num_ex_dem>300){
    printf("can not traverse, back and rescan \n");
    exit(1);
  }
  printf("%d\n",Num_ex_dem);
  Goal_ID = get_goal();
  pathplan(Goal_ID);
  return 0;
}
