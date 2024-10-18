#include "selection.h"

#define TEST_SIZE 1000
#define MAX_NUMBER 10000

int compare_ints(const void *a, const void *b)
{
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}

int main()
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

  qsort(test_sorted, TEST_SIZE, sizeof(int), compare_ints);

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
}
