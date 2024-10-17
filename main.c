#include <stdio.h>
#include <stdlib.h>

#define GROUP_SIZE 5

int compare_ints(const void *a, const void *b)
{
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  return (arg1 > arg2) - (arg1 < arg2);
}

int median(int *A, int size)
{ // constant time (propio)
  if (size == 0)
    size = GROUP_SIZE;
  qsort(A, size, sizeof(int), compare_ints);
  return A[(size - 1) / 2];
}

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int *A, int n)
{
  int x = A[0];
  int k = 0;
  for (int j = 1; j < n; j++)
  {
    if (A[j] <= x)
    {
      k++;
      swap(&A[k], &A[j]);
    }
  }
  swap(&A[0], &A[k]);
  return k;
}

int select_algorithm(int *A, int i, int n)
{
  if (n <= 0)
    return -1;
  if (n == 1)
    return 0;
  const int num_groups = n / GROUP_SIZE + (n % GROUP_SIZE == 0 ? 0 : 1);
  int medians[num_groups];
  for (int j = 0; j < num_groups; j++)
  {
    if (j == num_groups - 1)
      medians[j] = median(A + (j * GROUP_SIZE), n % GROUP_SIZE);
    else
      medians[j] = median(A + (j * GROUP_SIZE), 0);
  }

  int median_of_medians = select_algorithm(medians, (num_groups - 1) / 2, num_groups);

  for (int j = 0; i < n; j++)
  {
    if (A[j] == medians[median_of_medians])
    {
      median_of_medians = j;
      break;
    }
  }

  swap(&A[0], &A[median_of_medians]);

  int k = partition(A, n);

  if (i == k)
    return median_of_medians;
  else if (i < k)
    return select_algorithm(A, i, k + 1);
  else
    return select_algorithm(A + k, i - k, n - k);
}

int main()
{
  int v[] = {7, 2, 4, 3, 5, 4, 6, 8, 9, 5};
  printf("Res %d\n", select_algorithm(v, 2, 10));
  return 0;
}
