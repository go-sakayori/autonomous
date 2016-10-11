#include "grid_map.h"

int read_data(){

  int i=0;
  FILE *fp;
  float x0,y0,z0;


  if((fp = fopen("data3D.txt","r")) == NULL){
    printf("File not found\n");
    exit(0);
  }
  
  while(feof(fp)==0){
    fscanf(fp,"%f\t%f\t%f",&x0,&y0,&z0);
    x0 = 0.001 * x0;
    y0 = 0.001 * y0;
    z0 = 0.001 * z0;
    if(z0 < h_limit && -h_limit < z0 && x0 * x0 + y0 * y0 < dist_limit * dist_limit){
      vertex[i][0] = x0;
      vertex[i][1] = y0;
      vertex[i][2] = z0 + lrf_heigt;
      i++;
    }
  }
  fclose(fp);
  // printf("%d\n",i);
  return i-1;
}
 

void create_grid(int Point_Num){
  int i,j;
  float grid_interval = 0.5;
  float tmp_x,tmp_y;
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
  for(i=0;i<Point_Num;i++){
    tmp_x = (int) roundf(vertex[i][0]/grid_interval);
    tmp_y = (int) roundf(vertex[i][1]/grid_interval);
    dem_ID =  15 + tmp_y + tmp_x*32;

    if(dem[dem_ID][2]<vertex[i][2])
      dem[dem_ID][2] = vertex[i][2];
  }
  //printf("ok\n");
  //traverse or not for dem_ID
  //---------------------
  //        i+32
  //   i+1   i   i-1
  //        i-32
  //----------------------

}
