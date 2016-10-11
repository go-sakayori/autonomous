#include "common.h"
#include "grid_map.h"
#include "path_plan.h"
#include <stdio.h>

int main(){
  
 
  
  Point_Num = read_data();
  printf("Point Num? %d\n",Point_Num);
  create_grid(Point_Num);

  
  pathplan();
  return 0;
}
