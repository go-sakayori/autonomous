#include "common.h"
#include "grid_map.h"
#include "path_plan.h"
#include <stdio.h>

int main(){
  DEM dem[513];
  int i;
  Point_Num = read_data();
  printf("Point Num? %d\n",Point_Num); 

  Num_ex_dem = create_grid(Point_Num, dem);
  printf("%d\n",Num_ex_dem);
 
  /*if(Num_ex_dem>300)
    Num_ex_dem = create_grid(Point_Num,dem_h_limit+0.1);
  if(Num_ex_dem>300){
    printf("can not traverse, back and rescan \n");
    exit(1);
    }*/
  //printf("%d\n",Num_ex_dem);
  // for(i=0;i<512;i++)
  // printf("%f\t",(dem +i)->z);
  Goal_ID = get_goal(dem);
  pathplan(Goal_ID,dem);
  return 0;
}
