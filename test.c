#include "selection.h"

#define TEST_SIZE 1000
#define MAX_NUMBER 10000
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
    }

    int res = selection(test, i, TEST_SIZE);
    int res2 = test_sorted[i];
    if (res != res2)
    {
      printf("KO");
      return -1;
    }
  }
  printf("Ok\n");
  return 0;
}
