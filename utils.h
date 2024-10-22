#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#define RECURSION_LIMIT 10

/**
 * Compares two int based on their value
 *
 * @param a: pointer to the first int
 * @param b: pointer to the second int
 *
 * @return 1 if a > b,
 *         0 if a == b,
 *        -1 if a < b
 */
static int compare_int(const void *a, const void *b)
{
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}

/**
 * Naive implementation of the selection algorithm using qsort
 *
 * @param A: array of int
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 *
 * @return the i-th smallest element in the array
 */
static inline int qsort_selection(int *A, const int i, const int n)
{
  qsort(A, n, sizeof(int), compare_int);
  return A[i];
}

static inline void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * Partitions the array around the pivot element
 * After being partitioned the array will look like:
 * A = {less, eq, more}
 *      less = all the elements in A < than p
 *      eq = all the elements in A equals to p
 *      more = all the elements in A  > than p
 *
 * @param A: array of int
 * @param n: number of elements in the array
 * @param i: number of values lower than the element to find
 * @param pivot: value to partition the array
 *
 * @return the position of the pivot after partitioning
 */
static inline int partition(int *A, int n, int i, int pivot)
{
  int k = 0;
  for (int j = 0; j < n; j++)
  {
    if (A[j] < pivot)
    {
      swap(A + k, A + j);
      k++;
    }
  }
  int kEq = k;
  for (int j = k; j < n; j++)
  {
    if (A[j] == pivot)
    {
      swap(A + kEq, A + j);
      kEq++;
    }
  }

  if (i < k)
    return k;
  if (i < kEq)
    return i;
  return kEq - 1;
}

#endif