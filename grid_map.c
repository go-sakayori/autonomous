#include "grid_map.h"

int read_data(){

  int i=0;
  FILE *fp;
  float x0,y0,z0,a0,b0;


  if((fp = fopen("data3D.txt","r")) == NULL){
    printf("File not found\n");
    exit(0);
  }
  
  while(feof(fp)==0){
    fscanf(fp,"%f\t%f\t%f\t%f\t%f",&x0,&y0,&z0,&a0,&b0);
    /* x0 = 0.001 * x0;
    y0 = 0.001 * y0;
    z0 = 0.001 * z0;*/
    if(z0 < h_limit && -h_limit < z0 && x0*x0 + y0*y0 < dist_limit * dist_limit && 0 <= x0){
      // printf("%f\t%f\n",x0,y0);
      
      vertex[i][0] = x0;
      vertex[i][1] = y0;
      vertex[i][2] = z0 + lrf_heigt;
      i++;
    }
  }
  fclose(fp);
  //  printf("%f\t%f\n",vertex[i-1][0],vertex[i-1][1]);
  // printf("%d\n",i);
  //feofが一行多く読み込んでしまう．最後の行でx0が負の時，Point_Numに影響がでる
  if(x0 > 0)
    return i-1;
  else
    return i;
}
 

int create_grid(int Point_Num, float dem_h_limit){
  int i,j;
  float grid_interval = 0.5;
  int tmp_x,tmp_y;
  int dem_ID;
  //----------------
  //            x,i=15
  //             |
  //             | 
  //             |
  // y,j=31 -----0-----------j=0
  //--------------
  
  for(i=0;i<16;i++){
    for(j=0;j<32;j++){
      dem[i*32+j][0] = grid_interval/2 + i*grid_interval;
      dem[i*32+j][1] = grid_interval/2 + (j-16)*grid_interval;
      dem[i*32+j][2] = 0.0 ;
    }
  }
  //printf("%f,%f\n",dem[0][1],dem[511][1]);
  for(i=0;i<Point_Num;i++){
    tmp_x =  vertex[i][0]/grid_interval;
    tmp_y =  vertex[i][1]/grid_interval - 1;
    //printf("%d,%d\t",tmp_x,tmp_y);
    dem_ID =  16 + tmp_y + tmp_x*32;
    //printf("%d\n",dem_ID);
    
    if(fabs(dem[dem_ID][2]) < fabs(vertex[i][2]))
      dem[dem_ID][2] = vertex[i][2];
  }
  for(i=0;i<Grid_Num;i++){
    if(dem[i][2]==0.0)
      dem[i][2] = 123456789;
  }
  //printf("ok\n");
  //traverse or not for dem_ID
  //---------------------
  //        i+32
  //   i+1   i   i-1
  //        i-32
  //----------------------
  j=0;
  for(i=0;i<Grid_Num;i++){
    Ex_dem[i] = 0;
    if(dem[i][2] > dem_h_limit && dem[i][2] >= 0){
      Ex_dem[j] = i;
      j++;
    }
    else if(dem[i][2] < -dem_h_limit && dem[i][2] < 0){
      Ex_dem[j] = i;
      j++;
    }
  }
  return j;
}
