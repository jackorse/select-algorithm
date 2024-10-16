#include<iostream>

#define GROUP_SIZE 5

int compare_ints(const void* a, const void* b)
{
  int arg1 = *(const int*)a;
  int arg2 = *(const int*)b;

  return (arg1 > arg2) - (arg1 < arg2);
}
 


int median(int *A){ //constant time (propio)
  qsort(A, GROUP_SIZE, sizeof(int), compare_ints); 
  return A[2];
}


int select(int *A, int i, int n){
  int medians[n/GROUP_SIZE];
  for(int j =0;j < n/GROUP_SIZE; j++){
    medians[j] = median(A+(j*GROUP_SIZE));
  }

  

  return 0;
}


int main(){
  int v[] = {7,2,4,3,5};
  printf("median %d", median(v));
  return 0;
}

