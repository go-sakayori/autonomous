#include "path_plan.h"
#define LIMIT 12345678
#define N_dist 0.5/sqrt(2)

int get_goal(){
  int i;
  i=100;
  return i; 
  
}

void pathplan(int Goal_ID){

  float cost[Grid_Num];
  int prev[Grid_Num];
  int i,j;
  int next;
  int now;
  int min;
  int tmp_next;
  float tmp;
  
  cost[15] = calc_cost(1,15);
  cost[16] = calc_cost(1,16);

  if(cost[15]<cost[16])
    now = 15;
  else
    now = 16;
  do {
    min = 12345678;
    next = -1;

    //-------------------
    // +33    +32    +31
    // +1     now    -1
    // -31    -32    -33
    //-------------------
    
    for(j=0;j<8;j++){
      if(j==0)
        next = now - 1;
      else if(j==1)
        next = now + 1;
      else if(j==2)
        next = now + 32;
      else if(j==3)
        next = now + 31;
      else if(j==4)
        next = now + 33;
      else if(j==5)
        next = now - 32;
      else if(j==6)
        next = now - 31;
      else if(j==7)
        next = now - 33;
      if (next<0 || next>511)
        continue;
      
      tmp = calc_cost(now,next);
      if(cost[now] + tmp < cost[next]){
        cost[next] = cost[now] + tmp;
        prev[next] = now;
      }
      if(cost[next] < min){
        min = cost[next];
        tmp_next = next;
      }
    }
    
    now = tmp_next;
    
  } while( now != Goal_ID );

  //get path node
  
  
}

float calc_dist(int a ,int b){
  float dist;
  dist = sqrtf((dem[a][0] - dem[b][0])*(dem[a][0] - dem[b][0]) + (dem[a][1] - dem[b][1])*
               (dem[a][1] - dem[b][1]));
  return dist;

}


float calc_elev(int a ,int b){
  float pitch;

  pitch = atan2f((dem[b][2] - dem[a][2]),
                 sqrtf((dem[a][0] - dem[b][0])*(dem[a][0] - dem[b][0]) +
                       (dem[a][1] - dem[b][1])*(dem[a][1] - dem[b][1])));

  return pitch * 180 / (atan(1.0) * 4.0);
}

float calc_cost(int a ,int b){
  float cost;
  
  cost = calc_dist(a,b)/N_dist + calc_elev(a,b)/5;
  
  return cost;
  
}
