#include "grid_map.h"

int read_data(){

  int i=0;
  FILE *fp;
  float x0, y0, z0;


  if((fp = fopen("data3D.txt","r")) == NULL){
    printf("File not found\n");
    exit(0);
  }
  
  while(feof(fp)==0){
    fscanf(fp,"%f\t%f\t%f",&x0, &y0, &z0);
    if(fabs(z0) < H_LIMIT && x0 >= 0 && x0 < 8 && fabs(y0) < 8){
      vertex[i][0] = x0;
      vertex[i][1] = y0;
      vertex[i][2] = z0 + lrf_heigt;
      i++;
    }
  }
  fclose(fp);
  //feofが一行多く読み込んでしまう．最後の行でx0が負の時，Point_Numに影響がでる
  if(x0 > 0)
    return i-1;
  else
    return i;
}
 

int create_grid(int Point_Num, DEM *dem){
  int i, j;
  int tmp_x,tmp_y;
  int dem_ID;
  //----------------
  //            x,i=15
  //             |
  //             | 
  //             |
  // y,j=31 -----0-----------j=0
  //--------------
  
  for(i = 0; i < 16; i++){
    for(j = 0; j < 32; j++){
      (dem + i * 32 + j)->x = INTERVAL / 2 + i * INTERVAL;
      (dem + i * 32 + j)->y = INTERVAL / 2 + (j-16) * INTERVAL;
      (dem + i * 32 + j)->z = 0.0;
      (dem + i * 32 + j)->flag = true;
    }
  }
  
  for(i = 0; i < Point_Num; i++){
    tmp_x =   vertex[i][0] / INTERVAL;
    tmp_y =   vertex[i][1] / INTERVAL - 1;
    // printf("%d,%d\t",tmp_x,tmp_y);
    dem_ID =  16 + tmp_y + tmp_x * 32;
    printf("%d\t",dem_ID);
    if(fabs((dem + dem_ID)->z) < fabs(vertex[i][2])) //gets the maximum height (absolute) in the area
      (dem + dem_ID)->z = vertex[i][2];
  }

  // when there is no point cloud in a grid
  for(i=0;i<GRID_NUM;i++){
    if((dem + i)->z==0.0)
      (dem + i)->flag = false;
  }
  //printf("%f\n", (dem + 29)->z);

  //printf("ok\n");
  //traverse or not for dem_ID
  //---------------------
  //        i+32
  //   i+1   i   i-1
  //        i-32
  //----------------------
  j = 0;
  for(i = 0; i < GRID_NUM; i++){
    if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
      j++;
      (dem + i)->flag = false;
      if(i % 32 ==0){ //right area
        (dem + 1)->flag = false;
        if(i / 32 == 0) //bottom area
          (dem + 32)->flag = false;
        else if(i / 32 == 15) //top area
          (dem - 32)->flag = false;
        else{
          (dem + 32)->flag = false;
          (dem - 32)->flag = false;
        }
      }
      else if (i % 32 == 31){//left area
        (dem - 1)->flag = false;
        if(i / 32 == 0) //bottom area
          (dem + 32)->flag = false;
        else if(i / 32 == 15) //top area
          (dem - 32)->flag = false;
        else{
          (dem + 32)->flag = false;
          (dem - 32)->flag = false;
        }
      }
      else{
        (dem - 1)->flag = false;	
        (dem + 1)->flag = false;	
        (dem - 32)->flag = false;	
        (dem + 32)->flag = false;	
      }
    }
    else ;
  }
  return j;
}
