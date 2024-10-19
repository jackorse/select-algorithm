#include "selection.h"
#include "rand-select.h"
#include "qsort-select.h"
#include <assert.h>
#include <stdio.h>

#define REPETITIONS 1000
#define BIG_TEST_SIZE 10000
#define MEDIUM_TEST_SIZE 1000
#define SMALL_TEST_SIZE 100
#define TINY_TEST_SIZE 4
#define MAX_NUMBER 100000

/**
 * Macro to repeat a function a number of times
 * @param times: number of times to repeat the function
 * @param fn: function to be repeated
 */
#define repeat(times, fn)              \
  {                                    \
    for (int el = 0; el < times; el++) \
    {                                  \
      fn                               \
    }                                  \
  }

/**
 * Macro to initialize the arrays used in the tests with random values
 * @param original: array to be initialized and to be used in the qsort selection algorithm
 * @param rand_copy: copy of the original array to be used in the random selection algorithm
 * @param select_copy: copy of the original array to be used in the selection algorithm
 */
#define initialize_arrays(original, rand_copy, select_copy, size, max_value) \
  {                                                                          \
    for (int i = 0; i < size; i++)                                           \
    {                                                                        \
      original[i] = rand() % max_value;                                      \
      rand_copy[i] = original[i];                                            \
      select_copy[i] = original[i];                                          \
    }                                                                        \
  }

/* int main()
{
  int v[] = {7, 2, 4, 3, 5, 4, 6, 8, 9, 5};
  // 2,3,4,4,5,5,6,7,8,9,
  for (int i = 0; i < 10; i++)
  {
    printf("i = %d -> %d\n", i, selection(v, i, 10));
  }

  int test_original[TEST_SIZE];
  int test[TEST_SIZE];
  int test_rand[TEST_SIZE];
  int test_qsort[TEST_SIZE];
  int test_sorted[TEST_SIZE];
  for (int i = 0; i < TEST_SIZE; i++)
  {
    test_original[i] = rand() % MAX_NUMBER;
    test_sorted[i] = test_original[i];
  }

  qsort(test_sorted, TEST_SIZE, sizeof(int), compare_int);

  for (int i = 0; i < TEST_SIZE; i++)
  {
    for (int j = 0; j < TEST_SIZE; j++)
    {
      test[j] = test_original[j];
      test_rand[j] = test_original[j];
      test_qsort[j] = test_original[j];
    }

    int res = selection(test, i, TEST_SIZE);
    int res_rand = rand_selection(test_rand, i, TEST_SIZE);
    int res_qsort = rand_selection(test_qsort, i, TEST_SIZE);
    int res_ref = test_sorted[i];
    if (res != res_ref || res_rand != res_ref || res_qsort != res_ref)
    {
      printf("KO");
      return -1;
    }
  }
  printf("Ok\n");
  return 0;
} */

/**
 * Test the normal behaviour of the selection algorithm
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * If repetitions > test_size, repetitions = test_size
 */
void select_normal_behaviour(int test_size, int repetitions)
{
  int original[test_size], select_copy[test_size], rand_copy[test_size], res, res_qsort, res_rand;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, rand_copy, select_copy, test_size, MAX_NUMBER);
         res = selection(select_copy, el, test_size);
         res_rand = rand_selection(rand_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size););

  // Check if the element selected by the selection algorithm is the same as the one selected by qsort and rand_selection algorithms
  assert(res == res_qsort);
  assert(res_rand == res_qsort);
  printf("Test passed: [normal_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
}

/**
 * Test the behaviour of the selection algorithm when the array has duplicated elements
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * If repetitions > test_size, repetitions = test_size
 */
void select_duplicated_behaviour(int test_size, int repetitions, int max_value)
{
  int original[test_size], select_copy[test_size], rand_copy[test_size], res, res_qsort, res_rand;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, rand_copy, select_copy, test_size, max_value);
         res = selection(select_copy, el, test_size);
         res_rand = rand_selection(rand_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size););

  // Check if the element selected by the selection algorithm is the same as the one selected by qsort and rand_selection algorithms
  assert(res == res_qsort);
  assert(res_rand == res_qsort);
  printf("Test passed: [duplicated_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
}

/**
 * Start all tests
 */
void start_all_tests()
{
  // Test the normal behaviour of the selection algorithm with different test sizes
  select_normal_behaviour(TINY_TEST_SIZE, REPETITIONS);
  select_normal_behaviour(SMALL_TEST_SIZE, REPETITIONS);
  select_normal_behaviour(MEDIUM_TEST_SIZE, REPETITIONS);
  select_normal_behaviour(BIG_TEST_SIZE, REPETITIONS);

  // Test the behaviour of the selection algorithm when the array has duplicated elements with different test sizes
  select_duplicated_behaviour(TINY_TEST_SIZE, REPETITIONS, 10);
  select_duplicated_behaviour(SMALL_TEST_SIZE, REPETITIONS, 10);
  select_duplicated_behaviour(MEDIUM_TEST_SIZE, REPETITIONS, 10);
  select_duplicated_behaviour(BIG_TEST_SIZE, REPETITIONS, 10);

  // Test the behaviour of the selection algorithm when the array has all elements equal
  select_duplicated_behaviour(SMALL_TEST_SIZE, REPETITIONS, 1);
}

int main()
{
  start_all_tests();
  printf("All tests passed\n");
  return 0;
}
