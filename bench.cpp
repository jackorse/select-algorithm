#include <benchmark/benchmark.h>
#include "selection.h"
#include "qsort-select.h"
#include "rand-select.h"
#include <limits.h>

#define MAX_ELEMENTS 1 << 24
#define MIN_ELEMENTS 1 << 2
#define MAX_NUMBER INT_MAX

static void BM_Selection(benchmark::State &state)
{
  int size = state.range(0);

  // Perform setup here
  int *arr = (int*)malloc(size*sizeof(int));
  for (int i = 0; i < size; i++)
  {
    arr[i] = rand() % MAX_NUMBER;
  }
  for (auto _ : state)
  {
    // This code gets timed
    const int i = (size / 2); // rand() % (size-1);
    benchmark::DoNotOptimize(selection(arr, i, size));
  }
  free(arr);

  state.SetComplexityN(state.range(0));
}

// Register the function as a benchmark
BENCHMARK(BM_Selection)
    ->RangeMultiplier(2)
    ->Range(MIN_ELEMENTS, MAX_ELEMENTS)
    ->Complexity();

static void BM_Rand_Selection(benchmark::State &state)
{
  int size = state.range(0);

  // Perform setup here
  int *arr = (int*)malloc(size*sizeof(int));
  for (int i = 0; i < size; i++)
  {
    arr[i] = rand() % MAX_NUMBER;
  }
  for (auto _ : state)
  {
    // This code gets timed
    const int i = (size / 2); // rand() % (size-1);
    benchmark::DoNotOptimize(rand_selection(arr, i, size));
  }
  free(arr);

  state.SetComplexityN(state.range(0));
}
// Register the function as a benchmark
BENCHMARK(BM_Rand_Selection)
    ->RangeMultiplier(2)
    ->Range(MIN_ELEMENTS, MAX_ELEMENTS)
    ->Complexity();

static void BM_Qsort_Selection(benchmark::State &state)
{
  int size = state.range(0);
  int *arr = (int*)malloc(size*sizeof(int));

  // Perform setup here
  for (int i = 0; i < size; i++)
  {
    arr[i] = rand() % MAX_NUMBER;
  }
  for (auto _ : state)
  {
    // This code gets timed
    const int i = (size / 2); // rand() % (size-1);
    benchmark::DoNotOptimize(qsort_selection(arr, i, size));
  }
  free(arr);

  state.SetComplexityN(state.range(0));
}
// Register the function as a benchmark
BENCHMARK(BM_Qsort_Selection)
    ->RangeMultiplier(2)
    ->Range(MIN_ELEMENTS, MAX_ELEMENTS)
    ->Complexity();

// Run the benchmark
BENCHMARK_MAIN();
