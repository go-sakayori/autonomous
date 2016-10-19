#include "path_plan.h"
#define LIMIT 12345678
#define N_dist 0.5/sqrt(2)

int get_goal(DEM *dem){
  int i;
  i=508;
  
  if((dem + i)->flag ==0)
    i = i + 1;
  if((dem + i)->flag == 0)
    i = i - 2;
  return i; 
  
}

int pathplan(int Goal_ID, DEM * dem, Map map){
  int adjacent1[8]={-map.column-1, -map.column, -map.column+1, -1, 1, map.column-1, map.column, map.column+1};
  int adjacent2[5]={-map.column, -map.column+1, 1, map.column, map.column+1};
  int adjacent3[5]={-map.column-1, -map.column, -1, map.column-1, map.column};
  int adjacent4[5]={-1, 1, map.column-1, map.column, map.column+1};
  int adjacent5[5]={-1, 1, -map.column+1, -map.column, -map.column-1};
  int adjacent24[3]={1, map.column, map.column+1};
  int adjacent25[3]={1, -map.column-1, -map.column};
  int adjacent34[3]={-1, map.column-1, map.column};
  int adjacent35[3]={-1, -map.column, -map.column-1};

  int i, a, n = 0;
  float tmp[8];
  int goal_path;
  int now;

  //set start node
  (dem + 512)->x = 0.0;
  (dem + 512)->y = 0.0;
  (dem + 512)->z = 0.0;
  (dem + 512)->flag = 1;
  (dem + 512)->status = 1; //open start node
  
  //check near node from start
  if((dem + map.row - 1)->flag != 0){
    (dem + map.row - 1)->status = 1; //open node
    (dem + map.row - 1)->cost = calc_edge(512, map.row - 1, dem) + calc_dist(map.row - 1, Goal_ID, dem);
  }

  if((dem + map.row)->flag != 0){
    (dem + map.row)->status = 1; //open node
    (dem + map.row)->cost = calc_edge(512, map.row, dem) + calc_dist(1, Goal_ID, dem);
     }

 if((dem + map.row - 1)->flag == 0 && (dem + map.row)->flag == 0)
    printf("Cannnot move from start position");

  if((dem + map.row - 1)->cost < (dem + map.row)->cost){
    now = map.row - 1;
    (dem + now)->prev = 512;
  }
  else{
    now = map.row;
    (dem + now)->prev = 512;
  }
  (dem + 512)->status = 0; //close start node  
  
  while( now != Goal_ID ){
    now = sort_open(dem, map.point);
    (dem + now)->status = 0; //close now node
    a = (dem + now)->flag;
    
    switch (a){
    case 0:
      (dem + now)->status = 0; //close now node

      break;

    case 1:
      n = sizeof(adjacent1) / sizeof(adjacent1[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent1[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent1[i])->cost){
	  (dem + now + adjacent1[i])->status = 1;
	  (dem + now + adjacent1[i])->cost = tmp[i];
	  (dem + now + adjacent1[i])->prev = now;
	}
	else ;
      }

      break;

    case 2:
      n = sizeof(adjacent2) / sizeof(adjacent2[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent2[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent2[i])->cost){
	  (dem + now + adjacent2[i])->status = 1;
	  (dem + now + adjacent2[i])->cost = tmp[i];
	  (dem + now + adjacent2[i])->prev = now;
	}
	else ;
      }

      break;

    case 3:
      n = sizeof(adjacent3) / sizeof(adjacent3[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent3[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent3[i])->cost){
	  (dem + now + adjacent3[i])->status = 1;
	  (dem + now + adjacent3[i])->cost = tmp[i];
	  (dem + now + adjacent3[i])->prev = now;
	}
	else ;
      }

      break;

    case 4:
      n = sizeof(adjacent4) / sizeof(adjacent4[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent4[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent4[i])->cost){
	  (dem + now + adjacent4[i])->status = 1;
	  (dem + now + adjacent4[i])->cost = tmp[i];
	  (dem + now + adjacent4[i])->prev = now;
	}
	else ;
      }      

      break;

    case 5:
      n = sizeof(adjacent5) / sizeof(adjacent5[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent5[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent5[i])->cost){
	  (dem + now + adjacent5[i])->status = 1;
	  (dem + now + adjacent5[i])->cost = tmp[i];
	  (dem + now + adjacent5[i])->prev = now;
	}
	else ;
      }

      break;

    case 24:
      n = sizeof(adjacent24) / sizeof(adjacent24[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent24[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent24[i])->cost){
	  (dem + now + adjacent24[i])->status = 1;
	  (dem + now + adjacent24[i])->cost = tmp[i];
	  (dem + now + adjacent24[i])->prev = now;
	}
	else ;
      }      

      break;

    case 25:
      n = sizeof(adjacent25) / sizeof(adjacent25[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent25[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent25[i])->cost){
	  (dem + now + adjacent25[i])->status = 1;
	  (dem + now + adjacent25[i])->cost = tmp[i];
	  (dem + now + adjacent25[i])->prev = now;
	}
	else ;
      }
      
      break;

    case 34:
      n = sizeof(adjacent34) / sizeof(adjacent34[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent34[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent34[i])->cost){
	  (dem + now + adjacent34[i])->status = 1;
	  (dem + now + adjacent34[i])->cost = tmp[i];
	  (dem + now + adjacent34[i])->prev = now;
	}
	else ;
      }

      break;

    case 35:
      n = sizeof(adjacent35) / sizeof(adjacent35[0]);
      for(i=0; i<n; i++){
	tmp[i] = calc_cost(now, adjacent35[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent35[i])->cost){
	  (dem + now + adjacent35[i])->status = 1;
	  (dem + now + adjacent35[i])->cost = tmp[i];
	  (dem + now + adjacent35[i])->prev = now;
	}
	else ;
      }

      break;

    default:
      break;
    }
  }
  i = 0;
  goal_path = now;
  do{
    //printf("%d\n",goal_path);
    goal_path = (dem + goal_path)->prev;
    i++;
  }while(goal_path != 512);
 
  return i;
}

void create_motion(int Goal_ID, DEM *dem, int *motion, int size, int column){

  //////variable for motion table
  //   forward
  // 
  //  0   1   2
  //  3 robot 4
  //  5   6   7
  //
  // 8 for start to 15
  // 9 for start to 16
  //////
  int i;
  int tmp;
  int now = Goal_ID; 

  for(i=size-1; i >0; i--){
    tmp = now - (dem + now)->prev;
    now = (dem + now) -> prev;
    if(tmp == column + 1)
      motion[i] = 0;
    else if(tmp == column)
      motion[i] = 1;
    else if(tmp == column -1)
      motion[i] = 2;
    else if(tmp == 1)
      motion[i] = 3;
    else if(tmp == -1)
      motion[i] = 4;
    else if(tmp == 1 - column)
      motion[i] = 5;
    else if(tmp == -column)      
      motion[i] = 6;
    else if (tmp == -column - 1)
      motion[i] = 7;
    else
      printf("motion table not working\n");
  }
  if(now == column / 2 -1)
    motion[0] = 8;
  else if(now == column / 2)
    motion[0] = 9;
  else
    printf("motion table not working\n");
}

float calc_dist(int a ,int b, DEM *dem){
  float dist;
  dist = sqrtf(((dem + a)->x - (dem + b)->x)*((dem + a)->x - (dem + b)->x)
               + ((dem + a)->y - (dem + b)->y)*((dem + a)->y - (dem + b)->y));
  return dist;

}


float calc_elev(int a ,int b, DEM *dem){
  float pitch;

  pitch = atan2f(((dem + b)->z - (dem + a)->z),
                 sqrtf(((dem + a)->x - (dem + b)->x)*((dem + a)->x - (dem + b)->x)
                       + ((dem + a)->y - (dem + b)->y)*((dem + a)->y - (dem + b)->y)));

  pitch = fabs(pitch);
  return pitch * 180 / M_PI;
}

float calc_edge(int a ,int b,DEM *dem){
  float cost;
  
  cost = calc_dist(a,b,dem)/N_dist + calc_elev(a,b,dem)/5;
  return cost;
  
}

float calc_cost(int now, int adjacent, int Goal_ID, DEM *dem){
  float cost;
  cost = calc_edge(now, now + adjacent, dem) //cost between 2 nodes
    + (dem + now)->cost //minimum cost untill now
    - calc_dist(Goal_ID, now, dem) //now's heuristic function  
    + calc_dist(Goal_ID, now + adjacent, dem); //adjacent's heuristic function
  return cost;
}

int sort_open(DEM *dem, int grid_num){
  int i, num;
  float min = 12345678; 
  for(i=0; i<grid_num; i++){
    if((dem + i)->status == 1 && (dem + i)->cost < min){
      min = (dem + i)->cost;
      num = i;
    }
    else ;
  }
  return num;
}
