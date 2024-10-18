#include "selection.h"

/**
 * We needed to store the values of the elements in the original array, together with their relative offset in it.
 * To access them just use A[val.ptr - A], where val.ptr is the memory address of the integer and A is the array in which is stored. 
 */
typedef struct int_p
{
  int value;
  struct int_p *ptr;
} int_ptr;

/**
 * Compares two int_ptr based on their value
 *
 * @param a: pointer to the first int_ptr
 * @param b: pointer to the second int_ptr
 *
 * @return 1 if a > b,
 *         0 if a == b,
 *        -1 if a < b
 */
int compare_int_ptr(const void *a, const void *b)
{
  int_ptr arg1 = *(const int_ptr *)a;
  int_ptr arg2 = *(const int_ptr *)b;

  return (arg1.value > arg2.value) - (arg1.value < arg2.value);
}

/**
 * Returns the median of an array of int_ptr
 *
 * @param A: array of int_ptr
 * @param size: number of elements in the array
 *
 * @return the position of the median in the array
 */
int median(int_ptr *A, int size)
{ // constant time (propio)
  if (size == 0)
    size = GROUP_SIZE;
  qsort(A, size, sizeof(int_ptr), compare_int_ptr);
  return (size - 1) / 2;
}

void swap(int_ptr *a, int_ptr *b)
{
  int_ptr tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * Partitions the array around the first element (pivot)
 * After being partitioned the array will look like:
 * A = {less, p, more} 
 *      less = all the elements in A <= than p
 *      more = all the elements in A  > than p
 *
 * @param A: array of int_ptr
 * @param n: number of elements in the array
 *
 * @return the position of the pivot after partitioning
 */
int partition(int_ptr *A, int n)
{
  int x = A[0].value;
  int k = 0;
  for (int j = 1; j < n; j++)
  {
    if (A[j].value <= x)
    {
      k++;
      swap(A + k, A + j);
    }
  }
  swap(A, A + k);
  return k;
}

/**
 * Recursive function to find the i-th smallest element in an array
 *
 * @param A: array of integers
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 */
int_ptr select_algorithm(int_ptr *A, int i, int n)
{
  // Error case: just return -1
  if (n <= 0 || i < 0)
    return (int_ptr){.value = -1, .ptr = NULL};

  // Base case: if n = 1 and i = 0, return the only element
  //            if n = 1 and i != 0, something went wrong, return -1
  if (n == 1)
    if (i == 0)
      return A[0];
    else
      return (int_ptr){.value = -1, .ptr = NULL};

  // Move the median of medians to the first position
  swap(A, A[rand()%n]);

  // Partition the array around the median of medians,
  // and get the position of the median of medians (pivot)
  int k = partition(A, n);

  // If the pivot is the i-th element, return it,
  // otherwise, recursively find the i-th element in the lower or upper part
  if (i == k)
    return A[k];
  else if (i < k)
    return select_algorithm(A, i, k);
  else
    return select_algorithm(A + k + 1, i - k - 1, n - k - 1);
}

/**
 * Finds the i-th smallest element in an array
 *
 * @param A: array of integers
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 *
 * @return the i-th smallest element in the array
 */
int selection(int *A, int i, int n)
{
  // Convert the int array A to to an array of int_ptr,
  // that can be passed to the recursive function
  int_ptr A_ptr[n];

  for (int j = 0; j < n; j++)
  {
    A_ptr[j].ptr = NULL;
    A_ptr[j].value = A[j];
  }

  int_ptr res = select_algorithm(A_ptr, i, n);

  return res.value;
}
