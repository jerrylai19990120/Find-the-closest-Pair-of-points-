#include "closest_brute.h"
#include <stdio.h>

double brute_force(struct Point P[], size_t n) 
{ 
  double min_dist = dist(P[0], P[1]);
  double temp;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      temp = dist(P[i], P[j]);
      if(temp<min_dist){
        min_dist = temp;
      }
    }
  }
  return min_dist; 
} 
