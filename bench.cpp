#include <limits>
#include <stdio.h>
#include <benchmark/benchmark.h>
#include "selection.h"
#include "rand-select.h"
// Testing only
#include "select-online.hpp"

#define MAX_ELEMENTS 1 << 18
#define MIN_ELEMENTS 1 << 2
#define MAX_NUMBER INT_MAX

FILE *r = fopen("/dev/urandom", "r");

static void BM_Selection(benchmark::State &state)
{
  int size = state.range(0);
  // Perform setup here
  int *arr = (int *)malloc(size * sizeof(int));

  for (auto _ : state)
  {
    state.PauseTiming();
    if(fread(arr, sizeof(int), size, r) != size)
      printf("Failed to init the array\n");
    const int i = (size / 2); // rand() % (size-1);
    state.ResumeTiming();

    // This code gets timed
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
  int *arr = (int *)malloc(size * sizeof(int));

  for (auto _ : state)
  {
    state.PauseTiming();
    if(fread(arr, sizeof(int), size, r) != size)
      printf("Failed to init the array\n");
    const int i = (size / 2); // rand() % (size-1);
    state.ResumeTiming();

    // This code gets timed
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
  int *arr = (int *)malloc(size * sizeof(int));

  // Perform setup here
  for (auto _ : state)
  {
    state.PauseTiming();
    if (fread(arr, sizeof(int), size, r) != size)
      printf("Failed to init the array\n");
    const int i = (size / 2); // rand() % (size-1);
    state.ResumeTiming();
    // This code gets timed
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

// static void BM_Online_Selection(benchmark::State &state)
//{
//   int size = state.range(0);
//
//   // Perform setup here
//   std::vector<int> arr;
//
//   for (int i = 0; i < size; i++)
//   {
//     arr[i] = rand() % MAX_NUMBER;
//   }
//   std::vector<int> const v = arr;
//   for (auto _ : state)
//   {
//     // This code gets timed
//     const int i = (size / 2); // rand() % (size-1);
//     benchmark::DoNotOptimize(online_selection(v));
//   }
//
//   state.SetComplexityN(state.range(0));
// }
//// Register the function as a benchmark
// BENCHMARK(BM_Online_Selection)
//     ->RangeMultiplier(2)
//     ->Range(MIN_ELEMENTS, MAX_ELEMENTS)
//     ->Complexity();

// Run the benchmark
BENCHMARK_MAIN();
