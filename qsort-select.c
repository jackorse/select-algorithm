#include "qsort-select.h"

int compare_int(const void *a, const void *b)
{
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}


int qsort_selection(int *A, const int i, const int n)
{
  qsort(A, n, sizeof(int), compare_int);
  return A[i];
}