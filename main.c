#include <stdio.h>
#include <stdlib.h>

#define GROUP_SIZE 5

typedef struct
{
  int value;
  int *ptr;
} int_ptr;

/**
 * Returns 1 if arg1 > arg2
 *         0 if arg1 = arg2
 *        -1 if arg1 < arg2
 */
int compare_ints(const void *a, const void *b)
{
  int_ptr arg1 = *(const int_ptr *)a;
  int_ptr arg2 = *(const int_ptr *)b;

  return (arg1.value > arg2.value) - (arg1.value < arg2.value);
}

int_ptr median(int_ptr *A, int size)
{ // constant time (propio)
  if (size == 0)
    size = GROUP_SIZE;
  qsort(A, size, sizeof(int), compare_ints);
  return A[(size - 1) / 2];
}

void swap(int_ptr *a, int_ptr *b)
{
  int_ptr tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int_ptr *A, int n)
{
  int x = A[0].value;
  int k = 0;
  for (int j = 1; j < n; j++)
  {
    if (A[j].value <= x)
    {
      k++;
      swap(&A[k], &A[j]);
    }
  }
  swap(A, A + k);
  return k;
}

int_ptr select_algorithm(int_ptr *A, int i, int n)
{
  if (n <= 0)
    return (int_ptr){.value = -1, .ptr = NULL};
  if (n == 1)
    return *A;

  const int num_groups = n / GROUP_SIZE + (n % GROUP_SIZE == 0 ? 0 : 1);
  int_ptr medians[num_groups];
  for (int j = 0; j < num_groups; j++)
  {
    if (j == num_groups - 1)
      medians[j] = median(A + (j * GROUP_SIZE), n % GROUP_SIZE);
    else
      medians[j] = median(A + (j * GROUP_SIZE), 0);
  }

  int_ptr median_of_medians = select_algorithm(medians, (num_groups - 1) / 2, num_groups);

  // for (int j = 0; i < n; j++)
  // {
  //   if (A[j] == medians[median_of_medians])
  //   {
  //     median_of_medians = j;
  //     break;
  //   }
  // }

  swap(A, &median_of_medians);

  // position of the pivot after partition
  int k = partition(A, n);

  if (i == k)
    return median_of_medians;
  else if (i < k)
    return select_algorithm(A, i, k + 1);
  else
    return select_algorithm(A + k, i - k, n - k);
}

int selection(int *A, int i, int n)
{
  int_ptr A_ptr[n];

  for (int j = 0; j < i; j++)
  {
    A_ptr[j].ptr = A + j;
    A_ptr[j].value = A[j];
  }

  int_ptr res = select_algorithm(A_ptr, i, n);

  return res.value;
}

int main()
{
  int v[] = {7, 2, 4, 3, 5, 4, 6, 8, 9, 5};
  printf("Res %d\n", selection(v, 2, 10));
  return 0;
}
