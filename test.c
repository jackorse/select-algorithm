#include "selection.h"
#include "rand-select.h"
#include "qsort-select.h"
#include <assert.h>
#include <stdio.h>

#define REPETITIONS 1000
#define BIG_TEST_SIZE 10000
#define MEDIUM_TEST_SIZE 1000
#define SMALL_TEST_SIZE 100
#define TINY_TEST_SIZE 5
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
#define initialize_arrays(original, copy, size, max_value) \
  {                                                        \
    for (int i = 0; i < size; i++)                         \
    {                                                      \
      original[i] = rand() % max_value;                    \
      copy[i] = original[i];                               \
    }                                                      \
  }

/**
 * Test the normal behaviour of the selection algorithm
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * If repetitions > test_size, repetitions = test_size
 */
void select_normal_behaviour(int test_size, int repetitions)
{
  int original[test_size], select_copy[test_size], res, res_qsort;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, select_copy, test_size, MAX_NUMBER);
         res = selection(select_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size);
         assert(res == res_qsort););

  printf("Test passed: [select_normal_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
}

/**
 * Test the behaviour of the selection algorithm when the array has duplicated elements
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * @param max_value: maximum value of the elements in the array (used to generate random values)
 * If repetitions > test_size, repetitions = test_size
 */
void select_duplicated_behaviour(int test_size, int repetitions, int max_value)
{
  int original[test_size], select_copy[test_size], res, res_qsort;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, select_copy, test_size, max_value);
         res = selection(select_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size);
         assert(res == res_qsort););

  if (max_value != 1)
  {
    printf("Test passed: [select_some_duplicated_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
  }
  else
  {
    printf("Test passed: [select_all_duplicated_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
  }
}

/**
 * Test the normal behaviour of the random selection algorithm
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * If repetitions > test_size, repetitions = test_size
 */
void random_normal_behaviour(int test_size, int repetitions)
{
  int original[test_size], rand_copy[test_size], res_qsort, res_rand;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, rand_copy, test_size, MAX_NUMBER);
         res_rand = rand_selection(rand_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size);
         assert(res_rand == res_qsort););

  printf("Test passed: [random_normal_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
}

/**
 * Test the behaviour of the random selection algorithm when the array has duplicated elements
 * @param test_size: size of the array to test
 * @param repetitions: number of test's executions (every execution the selected element is different).
 * @param max_value: maximum value of the elements in the array (used to generate random values)
 * If repetitions > test_size, repetitions = test_size
 */
void random_duplicated_behaviour(int test_size, int repetitions, int max_value)
{
  int original[test_size], rand_copy[test_size], res_qsort, res_rand;
  int actual_repetitions = repetitions < test_size ? repetitions : test_size;

  // Repetitions are used to test the algorithm with different selected elements
  repeat(actual_repetitions,
         initialize_arrays(original, rand_copy, test_size, max_value);
         res_rand = rand_selection(rand_copy, el, test_size);
         res_qsort = qsort_selection(original, el, test_size);
         assert(res_rand == res_qsort););

  if (max_value != 1)
  {
    printf("Test passed: [random_some_duplicated_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
  }
  else
  {
    printf("Test passed: [random_all_duplicated_behaviour, test_size: %d, repetitions: %d]\n", test_size, actual_repetitions);
  }
}

/**
 * Start all tests.
 * With this battery of tests, we ensure that the deterministic and random selection algorithms work correctly by
 * comparing their results with the qsort selection algorithm's results.
 * The tests are divided into two categories: normal behaviour and duplicated behaviour. The first ones test the
 * algorithms' normal behaviour with certain test sizes and repetitions in order to ensure that the algorithms hasn't
 * guess the selected element only by chance. The second ones test the algorithms behaviour
 * when the array has a big number of duplicated elements to verify that the selection logic reacts correctly even with a
 * big number elements equals to each other.
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
  select_duplicated_behaviour(MEDIUM_TEST_SIZE, REPETITIONS, 1);

  // Test the normal behaviour of the random algorithm with different test sizes
  random_normal_behaviour(TINY_TEST_SIZE, REPETITIONS);
  random_normal_behaviour(SMALL_TEST_SIZE, REPETITIONS);
  random_normal_behaviour(MEDIUM_TEST_SIZE, REPETITIONS);
  random_normal_behaviour(BIG_TEST_SIZE, REPETITIONS);

  // Test the behaviour of the random algorithm when the array has duplicated elements with different test sizes
  random_duplicated_behaviour(TINY_TEST_SIZE, REPETITIONS, 10);
  random_duplicated_behaviour(SMALL_TEST_SIZE, REPETITIONS, 10);
  random_duplicated_behaviour(MEDIUM_TEST_SIZE, REPETITIONS, 10);
  random_duplicated_behaviour(BIG_TEST_SIZE, REPETITIONS, 10);

  // Test the behaviour of the random algorithm when the array has all elements equal
  random_duplicated_behaviour(BIG_TEST_SIZE, REPETITIONS, 1);
}

int main()
{
  start_all_tests();
  printf("All tests passed\n");
  return 0;
}
