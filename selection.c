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

  if (arg1.value < arg2.value)
    return -1;
  if (arg1.value > arg2.value)
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
static inline int_ptr median(int_ptr *A, int size)
{
  if (size == 0)
    size = GROUP_SIZE;
  qsort(A, size, sizeof(int_ptr), compare_int_ptr);
  const int offset = (size - 1) / 2;
  return (int_ptr){.value = A[offset].value, .ptr = NULL};
}

/**
 * Returns the maximum of two int_ptr
 *
 * @param a: pointer to the first int_ptr
 * @param b: pointer to the second int_ptr
 *
 * @return the int_ptr with the highest value
 */
static inline int_ptr *max(int_ptr *a, int_ptr *b)
{
  return a->value > b->value ? a : b;
}

/**
 * Returns the minimum of two int_ptr
 *
 * @param a: pointer to the first int_ptr
 * @param b: pointer to the second int_ptr
 *
 * @return the int_ptr with the lowest value
 */
static inline int_ptr *min(int_ptr *a, int_ptr *b)
{
  return a->value < b->value ? a : b;
}

/**
 * Returns the median of 5 elements
 *
 * @param A: Group of 5 int_ptr elements
 *
 * @return An int_ptr struct with the median value and its position in the array A
 */
static inline int_ptr median5(int_ptr *A)
{
  int_ptr *f = max(min(A, A + 1), min(A + 2, A + 3));       // discards lowest from first 4
  int_ptr *g = min(max(A, A + 1), max(A + 2, A + 3));       // discards biggest from first 4
  int_ptr *res = max(min(A + 4, f), min(g, max(A + 4, f))); // median3(A[4], f, g);
  return (int_ptr){.value = res->value, .ptr = NULL};
}

static inline void swap(int_ptr *a, int_ptr *b)
{
  int_ptr tmp = *a;
  *a = *b;
  *b = tmp;
}

/**
 * Partitions the array around the last element (pivot)
 * After being partitioned the array will look like:
 * A = {less, eq, more}
 *      less = all the elements in A < than p
 *      eq = all the elements in A equals to p
 *      more = all the elements in A  > than p
 *
 * @param A: array of int_ptr
 * @param n: number of elements in the array
 *
 * @return the position of the pivot after partitioning
 */
static inline int partition(int_ptr *A, int n, int i, int x)
{
  int p_index;
  for (int j = 0; j < n; j++)
  {
    if (A[j].value == x)
    {
      p_index = j;
      break;
    }
  }

  swap(A + p_index, A + n - 1);

  int k = 0;
  for (int j = 0; j < n - 1; j++)
  {
    if (A[j].value < x)
    {
      swap(A + k, A + j);
      k++;
    }
  }
  int kEq = k;
  for (int j = k; j < n - 1; j++)
  {
    if (A[j].value == x)
    {
      swap(A + kEq, A + j);
      kEq++;
    }
  }

  swap(A + n - 1, A + kEq);

  if (i < k)
    return k;
  if (i <= kEq)
    return i;
  return kEq;
}

/**
 * Recursive function to find the i-th smallest element in an array
 *
 * @param A: array of integers
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 */
int_ptr select_algorithm(int_ptr *A, const int i, const int n)
{
  // Error case: just return -1
  if (n <= 0 || i < 0 || i >= n)
    return (int_ptr){.value = -1, .ptr = NULL};

  // Base case: if n <= RECURSION_LIMIT, the recursion overhead is too high,
  // just use the naive algorithm
  if (n <= RECURSION_LIMIT)
  {
    qsort(A, n, sizeof(int_ptr), compare_int_ptr);
    return A[i];
  }

  // Divide the array into groups of GROUP_SIZE elements,
  // last group may have less than GROUP_SIZE elements
  const int num_groups = n / GROUP_SIZE + (n % GROUP_SIZE == 0 ? 0 : 1);

  // Find the medians for the first num_groups - 1 groups
  int_ptr *medians = (int_ptr *)malloc(num_groups * sizeof(int_ptr));
  for (int j = 0; j < num_groups - 1; j++)
  {
    medians[j] = median5(A + (j * GROUP_SIZE));
  }
  // Find the median for the last group (whose size may be less than GROUP_SIZE)
  medians[num_groups - 1] = median(A + ((num_groups - 1) * GROUP_SIZE), n % GROUP_SIZE);

  // Recursively find the median of medians
  int_ptr median_of_medians = select_algorithm(medians, (num_groups - 1) / 2, num_groups);
  free(medians);

  // Move the median of medians to the last position
  // swap(A  + n - 1, median_of_medians.ptr);

  // Partition the array around the median of medians,
  // and get the position of the median of medians (pivot)
  int k = partition(A, n, i, median_of_medians.value);

  // If the pivot is the i-th element, return it,
  // otherwise, recursively find the i-th element in the lower or upper part
  if (i == k)
    // Found the i-th element
    return A[k];
  else if (i < k)
    // Recursively find the i-th element in the lower part
    return select_algorithm(A, i, k);
  else
    // Recursively find the i-th element in the upper part
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
int selection(int *A, const int i, const int n)
{
  // Convert the int array A to to an array of int_ptr,
  // that can be passed to the recursive function
  int_ptr *A_ptr = (int_ptr *)malloc(n * sizeof(int_ptr));

  for (int j = 0; j < n; j++)
  {
    // A_ptr[j].ptr = NULL;
    A_ptr[j].value = A[j];
  }

  int_ptr res = select_algorithm(A_ptr, i, n);
  free(A_ptr);
  return res.value;
}
