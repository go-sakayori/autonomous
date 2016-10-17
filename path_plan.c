#include "path_plan.h"
#define LIMIT 12345678
#define N_dist 0.5/sqrt(2)

int get_goal(DEM *dem){
  int i;
  i=48;
  if((dem + i)->flag==false)
    i = i + 1;
  if((dem + i)->flag==false)
    i = i - 2;
  return i; 
  
}

void pathplan(int Goal_ID,DEM * dem){

  float cost[512];
  int prev[512];
  int i,j;
  int next;
  int now;
  int min;
  int tmp_next;
  float tmp;

  //set start node
  (dem + 512)->x = 0.0;
  (dem + 512)->y = 0.0;
  (dem + 512)->z = 0.0;
  (dem + 512)->flag = true;
  
  //check near node from start
  cost[15] = calc_cost(513,15,dem);
  cost[16] = calc_cost(513,16,dem);
  //printf("%d\n",Goal_ID);
  if(cost[15]<cost[16])
    tmp_next = 15;
  else
    tmp_next = 16;
  //  printf("%d\n",now);
  
  now = tmp_next;
  prev[now] = 512;
  //printf("%d\n",now);
  while( now != Goal_ID ){
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
      if((dem + next)->flag==false)
        continue;
      tmp = calc_cost(now,next,dem);
      if(cost[now] + tmp < cost[next]){
        cost[next] = cost[now] + tmp;
        prev[next] = now;
      }
      if(cost[next] < min){
        min = cost[next];
        tmp_next = next;
      }
    }
    if(now == tmp_next ){
      printf("%d\n",now);
      printf("path plan is failed\n");
      exit(0);
    }
    prev[tmp_next] = now;
    now = tmp_next;
    
  } 
  i = Goal_ID;
  //get path node 
  do{
    printf("iの前は%d\n",prev[i]);
    i = prev[i];
  }while(i!= 512);
  
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

  return pitch * 180 / (atan(1.0) * 4.0);
}

float calc_cost(int a ,int b,DEM *dem){
  float cost;
  
  cost = calc_dist(a,b,dem)/N_dist + calc_elev(a,b,dem)/5;
  
  return cost;
  
}
