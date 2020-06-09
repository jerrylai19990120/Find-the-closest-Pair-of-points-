#include "closest_parallel.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

int curr_depth = 0;

double _closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
  static int num_forks = 0;
  if(n<4 || pdmax==0){
    double result = _closest_serial(P, n);
    return result;
  }
  
 
  double minimum;
  int left_size = n / 2;
  int right_size = n - left_size;
  struct Point left_half[left_size];
  struct Point right_half[right_size];
  for(int i=0;i<left_size;i++){
    left_half[i] = P[i];
  }
  int count = left_size;
  for(int i=0;i<right_size;i++){
    right_half[i] = P[count];
    count++;
  }
  
  double middle_dist = dist(left_half[left_size-1], right_half[0]);
  qsort(left_half, left_size, sizeof(struct Point), compare_x);
  qsort(right_half, right_size, sizeof(struct Point), compare_x);
  int fd[2];
  if(pipe(fd)<0){
    exit(1);
  }
  
  int p_id = fork();
  
  if(p_id==0){
    num_forks++;
    close(fd[0]);
    double min_left = _closest_parallel(left_half, left_size, pdmax-1, pcount);
    write(fd[1], &min_left, sizeof(double));
    close(fd[1]);  
    exit(0);
  }
  
  
  int p_id2 = fork();
  
  if(p_id2==0){
    num_forks++;
    close(fd[0]);
    double min_right = _closest_parallel(right_half, right_size, pdmax-1, pcount);
    write(fd[1], &min_right, sizeof(double));
    close(fd[1]);  
    exit(0);
  }
  
  
  
  wait(&p_id);
  wait(&p_id2);
  
  close(fd[1]);
  double left_min;
  double right_min;

  read(fd[0], &left_min, sizeof(double));
  read(fd[0], &right_min, sizeof(double));
  close(fd[0]);
  
  //compare left, right and middle distances
  if(left_min>right_min){
    if(right_min>middle_dist){
      minimum = middle_dist;
    }else{
      minimum = right_min;
    }
  }else{
    if(left_min>middle_dist){
      minimum = middle_dist;
    }else{
      minimum = left_min;
    }
  }

  
  *pcount = num_forks;
  
  return minimum;
  
}

double closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
  qsort(P, n, sizeof(struct Point), compare_x);
  double minimum = _closest_parallel(P, n, pdmax, pcount);
  return minimum;
}
