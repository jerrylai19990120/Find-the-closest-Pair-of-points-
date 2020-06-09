#include "closest_helpers.h"
#include <math.h>

int verbose = 0;

int compare_x(const void* a, const void* b) 
{
  int result;
  int x1 = (*(struct Point*)a).x;
  int x2 = (*(struct Point*)b).x;
  if(x1-x2==0){
    result = 0;
  }else if(x1-x2>0){
    result = 1;
  }else{
    result = -1;
  }
  return result;
} 

int compare_y(const void* a, const void* b) 
{ 
  int result;
  int y1 = (*(struct Point*)a).y;
  int y2 = (*(struct Point*)b).y;
  if(y1-y2==0){
    result = 0;
  }else if(y1-y2>0){
    result = 1;
  }else{
    result = -1;
  }
  return result;
} 

double dist(struct Point p1, struct Point p2) 
{
  double horizontal;
  double vertical;
  if(p1.x > p2.x){
    horizontal = p1.x - p2.x;
  }else{
    horizontal = p2.x - p1.x;
  }
  
  if(p1.y > p2.y){
    vertical = p1.y - p2.y;
  }else{
    vertical = p2.y - p1.y;
  }
  
  double distance = sqrt(horizontal*horizontal+vertical*vertical);
    
  return distance;
} 


