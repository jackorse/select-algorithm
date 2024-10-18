#include <benchmark/benchmark.h>
#include "selection.h"

static void BM_Selection(benchmark::State& state) {
  int size=state.range(0);

  // Perform setup here
  int arr[size];
  for(int i =0;i<size;i++){
    arr[i]=rand();
  }
  for (auto _ : state) {
    // This code gets timed
    const int i = rand() % (size-1);
    benchmark::DoNotOptimize(selection(arr, i, size));
  }

  state.SetComplexityN(state.range(0));

}

// Register the function as a benchmark
BENCHMARK(BM_Selection)
    ->benchmark_min_time(3)
    ->RangeMultiplier(2)
    ->Range(1<<2, 1<<24)
    ->Complexity();

static void BM_Rand_Selection(benchmark::State& state) {
  int size=state.range(0);

  // Perform setup here
  int arr[size];
  for(int i =0;i<size;i++){
    arr[i]=rand();
  }
  for (auto _ : state) {
    // This code gets timed
    const int i = rand() % (size-1);
    benchmark::DoNotOptimize(rand_selection(arr, i, size));
  }

  state.SetComplexityN(state.range(0));

}
// Register the function as a benchmark
BENCHMARK(BM_Rand_Selection)
    ->benchmark_min_time(3)
    ->RangeMultiplier(2)
    ->Range(1<<2, 1<<24)
    ->Complexity();

// Run the benchmark
BENCHMARK_MAIN();
