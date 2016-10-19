#include "grid_map.h"
void create_grid(int point_num, DEM *dem, Map map){
  int i, j;
  int tmp_x,tmp_y;
  int dem_ID;

  //allocate memory for point cloud data
  float *vertex;
  vertex = (float*)malloc(sizeof(float) * point_num * 3);

  float tmp[3];
  FILE *fp;
  
  //initialize dem data
  for(i = 0; i < map.row; i++){
    for(j = 0; j < map.column; j++){
      (dem + i * map.column + j)->x = map.interval / 2 + i * map.interval;
      (dem + i * map.column + j)->y = map.interval / 2 + (j-16) * map.interval;
      (dem + i * 32 + j)->z = 0.0;
      (dem + i * 32 + j)->flag = 1;
      (dem + i * 32 + j)->status = 2;
      (dem + i * 32 + j)->cost = 999;
    }
  }

  //read point cloud data from txt data
  if((fp = fopen("data3D.txt","r")) == NULL){
    printf("File not found\n");
    exit(0);
  }

  for(i=0; i<point_num; i++){
    fscanf(fp,"%f\t%f\t%f",&tmp[0], &tmp[1], &tmp[2]);
    if(tmp[0] >= 0 && tmp[0] <map.size && fabs(tmp[1]) < map.size && fabs(tmp[2]) < map.threshold){
      vertex[i * 3 + 0] = tmp[0];
      vertex[i * 3 + 1] = tmp[1];
      vertex[i * 3 + 2] = tmp[2] + lrf_heigt;
      }
  }
  
  fclose(fp);
  
  //place maximum (or minimum) height to the gird
  for(i=0; i<point_num; i++){
    tmp_x = vertex[i * 3 + 0] / map.interval;
    tmp_y = vertex[i * 3 + 1] / map.interval;
    if(vertex[i * 3 + 1]<0)
      tmp_y = tmp_y - 1;
    dem_ID =  map.row + tmp_y + tmp_x * map.column;

    if(fabs((dem + dem_ID)->z) < fabs(vertex[i * 3 + 2]))
      (dem + dem_ID)->z = vertex[i * 3 + 2];
  }

  //memory release
  free(vertex);

  //traverse or not for dem_ID
  //---------------------
  //        i+32
  //   i+1   i   i-1
  //        i-32
  //----------------------

  for(i = 0; i < map.point; i++){
    if(i % map.column == 0){//right area
      if(i / map.column == 0){ //bottom area
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i + 1)->flag = 0;
	  (dem + i + map.column)->flag = 0;
	}
	else 
	  (dem + i)->flag = 24;
      }
      else if(i / map.column == (map.row -1)){ //top area
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i + 1)->flag = 0;
	  (dem + i - map.column)->flag = 0;
	}
	else 
	  (dem + i)->flag = 25;
      }
      else{ //not right-top or right-bottom
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i + 1)->flag = 0;
	  (dem + i - map.column)->flag = 0;
	  (dem + i + map.column)->flag = 0;
	}
	else if((dem + i)->flag != 0)
	  (dem + i)->flag = 2;
	else ;
      }
    }

    else if(i % map.column == (map.column - 1)){//left area
      if(i / map.column == 0){ //bottom area
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i - 1)->flag = 0;
	  (dem + i + map.column)->flag = 0;
	}
	else 
	  (dem + i)->flag = 34;
      }
      else if(i / map.column == (map.row - 1)){ //top area
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i - 1)->flag = 0;
	  (dem + i - map.column)->flag = 0;
	}
	else 
	  (dem + i)->flag = 35;
      }
      else{ //not left-top or left-bottom
	if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	  (dem + i)->flag = 0;
	  (dem + i - 1)->flag = 0;
	  (dem + i - map.column)->flag = 0;
	  (dem + i + map.column)->flag = 0;
	}
	else if((dem + i)->flag != 0)
	  (dem + i)->flag = 3;
	else ;
      }
    }


    else if(i / map.column == 0){ //bottom area
      if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	(dem + i)->flag = 0;
	(dem + i - 1)->flag = 0;
	(dem + i + 1)->flag = 0;
	(dem + i + map.column)->flag = 0;
      }
      else
	(dem + i)->flag = 4;
    }

    else if(i / map.column == (map.row - 1)){ //top area
      if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	(dem + i)->flag = 0;
	(dem + i - 1)->flag = 0;
	(dem + i + 1)->flag = 0;
	(dem + i - map.column)->flag = 0;
      }
      else
	(dem + i)->flag = 5;
    }
    else{
      if(fabs((dem + i)->z) > DEM_H || (dem + i)->z == 0.0){
	(dem + i)->flag = 0;
	(dem + i + 1)->flag = 0;
	(dem + i - 1)->flag = 0;
	(dem + i - map.column)->flag = 0;
	(dem + i + map.column)->flag = 0;
      }
      else ;
    }
  }
}
  
