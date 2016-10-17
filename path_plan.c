#include "path_plan.h"
#define LIMIT 12345678
#define N_dist 0.5/sqrt(2)

int get_goal(DEM *dem){
  int i;
  i=48;
  if((dem + i)->flag ==0)
    i = i + 1;
  if((dem + i)->flag == 0)
    i = i - 2;
  return i; 
  
}

void pathplan(int Goal_ID,DEM * dem){
  int adjacent1[8]={-33, -32, -31, -1, 1, 31, 32, 33};
  int adjacent2[5]={-32, -31, 1, 32, 33};
  int adjacent3[5]={-33, -32, -1, 31, 32};
  int adjacent4[5]={-1, 1, 31, 32, 33};
  int adjacent5[5]={-1, 1, -31, -32, -33};
  int adjacent24[3]={1, 32, 33};
  int adjacent25[3]={1, -31, -32};
  int adjacent34[3]={-1, 31, 32};
  int adjacent35[3]={-1, -32, -33};



  int i, a, tmp_node;
  float tmp[8];
  int goal_path;
  int now;

  //set start node
  (dem + 512)->x = 0.0;
  (dem + 512)->y = 0.0;
  (dem + 512)->z = 0.0;
  (dem + 512)->flag = 1;
  (dem + 512)->status = true; //open start node
  
  //check near node from start
  if((dem + 15)->flag == 1){
    (dem + 15)->status = true; //open node
    (dem + 15)->cost = calc_edge(512, 15, dem) + calc_dist(15, Goal_ID, dem);
  }

  if((dem + 16)->flag == 1){
    (dem + 15)->status = true; //open node
    (dem + 16)->cost = calc_edge(512, 16, dem) + calc_dist(16, Goal_ID, dem);
     }

 if((dem + 16)->flag == 0 && (dem + 16)->flag == 0)
    printf("Cannnot move from start position");

  if((dem + 15)->cost < (dem + 16)->cost){
    now = 15;
    (dem + now)->prev = 512;
  }
  else{
    now = 16;
    (dem + now)->prev = 512;
  }
  (dem + 512)->status = false; //close start node  

  while( now != Goal_ID ){
    a = (dem + now)->flag;
    switch (a){
    case 0:
      (dem + now)->status = false; //close now node

      break;

    case 1:
      for(i=0; i<(int)sizeof(adjacent1); i++){
	tmp[i] = calc_cost(now, adjacent1[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent1[i])->cost){
	  (dem + now + adjacent1[i])->status = true;
	  (dem + now + adjacent1[i])->cost = tmp[i];
	  (dem + now + adjacent1[i])->prev = now;
	}
	else ;
      }


      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;

      break;

    case 2:
      for(i=0; i<(int)sizeof(adjacent2); i++){
	tmp[i] = calc_cost(now, adjacent2[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent2[i])->cost){
	  (dem + now + adjacent2[i])->status = true;
	  (dem + now + adjacent2[i])->cost = tmp[i];
	  (dem + now + adjacent2[i])->prev = now;
	}
	else ;
      }

      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;

      break;

    case 3:
      for(i=0; i<(int)sizeof(adjacent3); i++){
	tmp[i] = calc_cost(now, adjacent3[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent3[i])->cost){
	  (dem + now + adjacent3[i])->status = true;
	  (dem + now + adjacent3[i])->cost = tmp[i];
	  (dem + now + adjacent3[i])->prev = now;
	}
	else ;
      }

      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;

      break;

    case 4:
      for(i=0; i<(int)sizeof(adjacent4); i++){
	tmp[i] = calc_cost(now, adjacent4[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent4[i])->cost){
	  (dem + now + adjacent4[i])->status = true;
	  (dem + now + adjacent4[i])->cost = tmp[i];
	  (dem + now + adjacent4[i])->prev = now;
	}
	else ;
      }      

      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;

      break;

    case 5:
      for(i=0; i<(int)sizeof(adjacent5); i++){
	tmp[i] = calc_cost(now, adjacent5[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent5[i])->cost){
	  (dem + now + adjacent5[i])->status = true;
	  (dem + now + adjacent5[i])->cost = tmp[i];
	  (dem + now + adjacent5[i])->prev = now;
	}
	else ;
      }
      
      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node; 

      break;

    case 24:
      for(i=0; i<(int)sizeof(adjacent24); i++){
	tmp[i] = calc_cost(now, adjacent24[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent24[i])->cost){
	  (dem + now + adjacent24[i])->status = true;
	  (dem + now + adjacent24[i])->cost = tmp[i];
	  (dem + now + adjacent24[i])->prev = now;
	}
	else ;
      }      

      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;  

      break;

    case 25:
      for(i=0; i<(int)sizeof(adjacent25); i++){
	tmp[i] = calc_cost(now, adjacent25[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent25[i])->cost){
	  (dem + now + adjacent25[i])->status = true;
	  (dem + now + adjacent25[i])->cost = tmp[i];
	  (dem + now + adjacent25[i])->prev = now;
	}
	else ;
      }
      
      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;
      
      break;

    case 34:
      for(i=0; i<(int)sizeof(adjacent34); i++){
	tmp[i] = calc_cost(now, adjacent34[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent34[i])->cost){
	  (dem + now + adjacent34[i])->status = true;
	  (dem + now + adjacent34[i])->cost = tmp[i];
	  (dem + now + adjacent34[i])->prev = now;
	}
	else ;
      }
      
      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node; 

      break;

    case 35:
      for(i=0; i<(int)sizeof(adjacent35); i++){
	tmp[i] = calc_cost(now, adjacent35[i], Goal_ID, dem);
	if(tmp[i] < (dem + now + adjacent35[i])->cost){
	  (dem + now + adjacent35[i])->status = true;
	  (dem + now + adjacent35[i])->cost = tmp[i];
	  (dem + now + adjacent35[i])->prev = now;
	}
	else ;
      }
      
      tmp_node = sort_open(dem);
      (dem + tmp_node)->prev = now; //path
      (dem + now)->status = false; //close now node
      now = tmp_node;

      break;
    }
  }
   
  goal_path = now;
  i=0;
  do{
    printf("%d\n",goal_path);
    goal_path = (dem + goal_path)->prev;
    i++;
    if(i>10)
      break;
  }while(goal_path != 512);
  
}

float calc_dist(int a ,int b,DEM *dem){
  float dist;
  dist = sqrtf(((dem + a)->x - (dem + b)->x)*((dem + a)->x - (dem + b)->x)
               + ((dem + a)->y - (dem + b)->y)*((dem + a)->y - (dem + b)->y));
  return dist;

}


float calc_elev(int a ,int b,DEM *dem){
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

int sort_open(DEM *dem){
  int i, num;
  float min = 12345678; 
  for(i=0; i<512; i++){
    if((dem + i)->status == true && (dem + i)->cost < min){
      min = (dem + i)->cost;
      num = i;
    }
  }
  return num;
}
