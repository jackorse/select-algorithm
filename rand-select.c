#include "rand-select.h"

static inline void swap(int *a, int *b)
{
    int tmp = *a;
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
int partition(int *A, int n)
{
    int x = A[0];
    int k = 0;
    for (int j = 1; j < n; j++)
    {
        if (A[j] <= x)
        {
            k++;
            swap(A + k, A + j);
        }
    }
    swap(A, A + k);
    return k;
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
int rand_selection(int *A, const int i, const int n)
{
    // Error case: just return -1
    if (n <= 0 || i < 0)
        return -1;

    // Base case: if n = 1 and i = 0, return the only element
    //            if n = 1 and i != 0, something went wrong, return -1
    if (n == 1)
    {
        if (i == 0)
            return A[0];
        else
            return -1;
    }

    // Move the a random number of the array to the first position
    swap(A, &A[rand() % n]);

    // Partition the array around the random number we choose,
    // and get the position of the pivot
    int k = partition(A, n);

    // If the pivot is the i-th element, return it,
    // otherwise, recursively find the i-th element in the lower or upper part
    if (i == k)
        return A[k];
    else if (i < k)
        return rand_selection(A, i, k);
    else
        return rand_selection(A + k + 1, i - k - 1, n - k - 1);
}
