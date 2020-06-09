#include "closest_serial.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double combine_lr(struct Point P[], size_t n, struct Point mid_point, double d)
{
  double min_dist;
 
  int num = 0;
  for(int i=0;i<n;i++){
    if(abs(P[i].x-mid_point.x) < d){
      num++;
    }
  }
  if(num==1){
    min_dist = d;
    return min_dist;
  }
  struct Point P2[num];
  int count = 0;
  for(int i=0;i<n;i++){
    if(abs(P[i].x-mid_point.x) < d){
      P2[count] = P[i];
      count++;
    }
  }
  
  qsort(P2, num, sizeof(struct Point), compare_y);
  double temp;
  min_dist = dist(P2[0],P2[1]);
  for(int i=0;i<num;i++){
    for(int j=i+1;j<num;j++){
      if(abs(P2[j].y-P2[i].y)<d){
        temp = dist(P2[j], P2[i]);
      }else{
        continue;
      }
      if(temp<min_dist){
        min_dist = temp;
      }
    }
  }
  
  
  return min_dist;
}

double _closest_serial(struct Point P[], size_t n)
{ 
  
  if(n<=3){
    double minimum_dist = brute_force(P, n);
    return minimum_dist;
  }
  double min_dist;
  int left_size = floor(n/2);
  int right_size = n - left_size;
 
  struct Point left[left_size];
  struct Point right[right_size];
  for(int i=0;i<left_size;i++){
    left[i] = P[i];
  }
  int count = left_size;
  for(int i=0;i<right_size;i++){
    right[i] = P[count];
    count++;
  }
  
  double dl = _closest_serial(left, left_size);
  double dr = _closest_serial(right, right_size);
  if(dl > dr){
    if(n%2!=0){
      min_dist = combine_lr(P, n, P[left_size], dr);
    }else{
      min_dist = combine_lr(P, n, P[left_size-1], dr);
    }
  }else{
    if(n%2!=0){
      min_dist = combine_lr(P, n, P[left_size], dl);
    }else{
      min_dist = combine_lr(P, n, P[left_size-1], dl);
    }
  }
 
  if(dl>dr){
    if(dr>min_dist){
      return min_dist;
    }else{
      return dr;
    }
  }else{
    if(dl>min_dist){
      return min_dist;
    }else{
      return dl;
    }
  }
  
  
}

double closest_serial(struct Point P[], size_t n)
{
  qsort(P, n, sizeof(struct Point), compare_x);
  double minimum = _closest_serial(P, n);
  return minimum;
}
