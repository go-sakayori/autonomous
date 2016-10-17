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
  float cost[512];
  int prev[512];
  int i,j, a;
  int next;
  int now;
  int min;
  int tmp_next;
  float tmp;

  for(i=0; i<512; i++)//initialize cost
    cost[i]=LIMIT;

  //set start node
  (dem + 512)->x = 0.0;
  (dem + 512)->y = 0.0;
  (dem + 512)->z = 0.0;
  (dem + 512)->flag = 1;
  (dem + 512)->status = true; //open start node
  (dem + 512)->score = calc_dist(512, Goal_ID, dem);
  
  //check near node from start
  if((dem + 15)->flag == 1){
    (dem + 15)->status = true; //open node
    (dem + 15)->cost = calc_edge(512, 15, dem);
    (dem + 15)->score = (dem + 15)->cost + calc_dist(15, Goal_ID, dem); //distance as heuristic function
  }
if((dem + 16)->flag == 1){
    (dem + 15)->status = true; //open node
    (dem + 16)->cost = calc_edge(512, 16, dem);
    (dem + 16)->score = (dem + 16)->cost + calc_dist(16, Goal_ID, dem); //distance as heuristic function
  }
 if((dem + 16)->flag == 0 && (dem + 16)->flag == 0)
    printf("Cannnot move from start position");

  if((dem + 15)->score < (dem + 16)->score){
    now = 15;
    (dem + now)->prev = 512;
  }
  else{
    now = 16;
    (dem + now)->prev = 512;
  }
  (dem + 512)->status = false; //close start node  
  //now = tmp_next;
  //prev[now] = 512;

  while( now != Goal_ID ){
    min = 12345678;
    next = -1;
    
    a = (dem + now)->flag;
    switch (a){
    case 1:
      (dem + now - 1)->status = (dem + now + 1)->status = (dem + now - 33)->status = (dem + now - 32)->status = (dem + now - 31)->status = (dem + now + 31)->status = (dem + now + 32)->status = (dem + now + 33)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

      (dem + now)->status = false; //close now node
      min = min_node(now+1, now -1, now - 31, now -32, now - 33, now + 31, now + 32, now + 33, dem); //calculate minimum score
      (dem + min)->prev = now; //path
      now = min; //next node

    case 2:
      (dem + now + 1)->status = (dem + now - 32)->status = (dem + now - 31)->status = (dem + now + 32)->status = (dem + now + 33)->status = true;

      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 3:
      (dem + now - 1)->status = (dem + now - 33)->status = (dem + now - 32)->status = (dem + now + 31)->status = (dem + now + 32)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 4:
      (dem + now - 1)->status = (dem + now + 1)->status = (dem + now + 31)->status = (dem + now + 32)->status = (dem + now + 33)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 5:
      (dem + now - 1)->status = (dem + now + 1)->status = (dem + now - 33)->status = (dem + now - 32)->status = (dem + now - 31)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 24:
      (dem + now + 1)->status = (dem + now + 32)->status = (dem + now + 33)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 25:
      (dem + now + 1)->status = (dem + now - 32)->status = (dem + now - 31)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 34:
      (dem + now - 1)->status = (dem + now + 32)->status = (dem + now + 31)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);

    case 35:
      (dem + now - 1)->status = (dem + now - 32)->status = (dem + now - 33)->status = true;

      (dem + now - 1)->cost = calc_edge(now, now - 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 1)->cost = calc_edge(now, now + 1, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 31)->cost = calc_edge(now, now - 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 32)->cost = calc_edge(now, now - 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now - 33)->cost = calc_edge(now, now - 33, dem) +(dem + (dem + now)->prev)->cost;
      (dem + now + 31)->cost = calc_edge(now, now + 31, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 32)->cost = calc_edge(now, now + 32, dem) + (dem + (dem + now)->prev)->cost;
      (dem + now + 33)->cost = calc_edge(now, now + 33, dem) + (dem + (dem + now)->prev)->cost;

      (dem + now - 1)->score = (dem + now - 1)->cost + calc_dist(Goal_ID, now - 1, dem);
      (dem + now + 1)->score = (dem + now + 1)->cost + calc_dist(Goal_ID, now + 1, dem);
      (dem + now - 31)->score = (dem + now - 31)->cost + calc_dist(Goal_ID, now - 31, dem);
      (dem + now - 32)->score = (dem + now - 32)->cost + calc_dist(Goal_ID, now - 32, dem);
      (dem + now - 33)->score = (dem + now - 33)->cost + calc_dist(Goal_ID, now - 33, dem);
      (dem + now + 31)->score = (dem + now + 31)->cost + calc_dist(Goal_ID, now + 31, dem);
      (dem + now + 32)->score = (dem + now + 32)->cost + calc_dist(Goal_ID, now + 32, dem);
      (dem + now + 33)->score = (dem + now + 33)->cost + calc_dist(Goal_ID, now + 33, dem);
    }

    //-------------------
    // +33    +32    +31
    // +1     now    -1
    // -31    -32    -33
    //-------------------
    /*   for(j=0;j<8;j++){
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
      tmp = calc_edge(now, next, dem);
      
      if(cost[now] + tmp < cost[next]){
	//printf("%d\t%f\t%f\t%f\n",j,cost[now],tmp,cost[next]);
        cost[next] = cost[now] + tmp;
        prev[next] = now;
	if(cost[next] < min){
	  min = cost[next];
	  tmp_next = next;
	}
      }
      
    }
    if(now == tmp_next ){
      printf("%d\n",now);
      printf("path plan is failed\n");
      exit(0);
    }
    prev[tmp_next] = now;
    now = tmp_next;
    printf("now:%d\n",now);
  } 
   i = Goal_ID;
  //get path node 
  do{
    printf("iの前は%d\n",prev[i]);
    i = prev[i];
  }while(i != 512);
    */  
  }
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


int min_node(int a, int b, int c, int d, int e, int f, int g, int h, DEM *dem){
  int i;
  float min=12345;
  int array[8]={a, b, c, d, e, f, g, h};
  int tmp;

  for(i=0; i<8; i++){
    if((dem+array[i])->score < min){
      min = (dem + array[i])->score;
      tmp = array[i];
    }
  }
  return tmp;
}

