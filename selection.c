#include "selection.h"

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
 * Returns the median of an array of int_ptr
 *
 * @param A: array of int_ptr
 * @param size: number of elements in the array
 *
 * @return the position of the median in the array
 */
static inline int median(int *A, int size)
{
  if (size == 0)
    size = GROUP_SIZE;
  qsort(A, size, sizeof(int), compare_int);
  const int offset = (size - 1) / 2;
  return A[offset];
}

/**
 * Returns the maximum of two int_ptr
 *
 * @param a: pointer to the first int_ptr
 * @param b: pointer to the second int_ptr
 *
 * @return the int_ptr with the highest value
 */
static inline int max(int a, int b)
{
  return a > b ? a : b;
}

/**
 * Returns the minimum of two int_ptr
 *
 * @param a: pointer to the first int_ptr
 * @param b: pointer to the second int_ptr
 *
 * @return the int_ptr with the lowest value
 */
static inline int min(int a, int b)
{
  return a < b ? a : b;
}

/**
 * Returns the median of 5 elements
 *
 * @param A: Group of 5 int_ptr elements
 *
 * @return An int_ptr struct with the median value and its position in the array A
 */
static inline int median5(int *A)
{
  int f = max(min(A[0], A[1]), min(A[2], A[3]));  // discards lowest from first 4
  int g = min(max(A[0], A[1]), max(A[2], A[3]));  // discards biggest from first 4
  return max(min(A[4], f), min(g, max(A[4], f))); // median3(A[4], f, g);
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
 * @param A: array of int_ptr
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


/**
 * Finds the i-th smallest element in an array
 *
 * @param A: array of integers
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 *
 * @return the i-th smallest element in the array
 */
int selection(int *A, const int i, const int n)
{
  // Error case: just return -1
  if (n <= 0 || i < 0 || i >= n)
    return -1;

  // Base case: if n <= RECURSION_LIMIT, the recursion overhead is too high,
  // just use the naive algorithm
  if (n <= RECURSION_LIMIT)
  {
    qsort(A, n, sizeof(int), compare_int);
    return A[i];
  }

  // Divide the array into groups of GROUP_SIZE elements,
  // last group may have less than GROUP_SIZE elements
  const int num_groups = n / GROUP_SIZE + (n % GROUP_SIZE == 0 ? 0 : 1);

  // Find the medians for the first num_groups - 1 groups
  int *medians = (int *)malloc(num_groups * sizeof(int));
  for (int j = 0; j < num_groups - 1; j++)
  {
    medians[j] = median5(A + (j * GROUP_SIZE));
  }
  // Find the median for the last group (whose size may be less than GROUP_SIZE)
  medians[num_groups - 1] = median(A + ((num_groups - 1) * GROUP_SIZE), n % GROUP_SIZE);

  // Recursively find the median of medians
  int median_of_medians = selection(medians, (num_groups - 1) / 2, num_groups);
  free(medians);

  // Move the median of medians to the last position
  // swap(A  + n - 1, median_of_medians.ptr);

  // Partition the array around the median of medians,
  // and get the position of the median of medians (pivot)
  int k = partition(A, n, i, median_of_medians);

  // If the pivot is the i-th element, return it,
  // otherwise, recursively find the i-th element in the lower or upper part
  if (i == k)
    // Found the i-th element
    return A[k];
  else if (i < k)
    // Recursively find the i-th element in the lower part
    return selection(A, i, k);
  else
    // Recursively find the i-th element in the upper part
    return selection(A + k + 1, i - k - 1, n - k - 1);
}
