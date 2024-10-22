#include "rand-select.h"

/**
 * Finds the i-th smallest element in an array
 *
 * @param A: array of integers
 * @param i: number of values lower than the element to find
 * @param n: number of elements in the array
 * @param worst_case: if true, the pivot is the first element in the array (worst case if the input array is sorted)
 *
 * @return the i-th smallest element in the array
 */
int rand_selection(int *A, const int i, const int n, bool worst_case)
{
    // Error case: just return -1
    if (n <= 0 || i < 0 || i >= n)
        return -1;

    // Base case: if n <= RECURSION_LIMIT, the recursion overhead is too high,
    // just use the naive algorithm
    if (n <= RECURSION_LIMIT)
    {
        return qsort_selection(A, i, n);
    }

    int pivot = worst_case ? A[0] : A[rand() % n];

    // Partition the array around the random number we choose,
    // and get the position of the pivot
    int k = partition(A, n, i, pivot);

    // If the pivot is the i-th element, return it,
    // otherwise, recursively find the i-th element in the lower or upper part
    if (i == k)
        return A[k];
    else if (i < k)
        return rand_selection(A, i, k, worst_case);
    else
        return rand_selection(A + k + 1, i - k - 1, n - k - 1, worst_case);
}
