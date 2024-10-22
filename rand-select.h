#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

#define RECURSION_LIMIT 10

int rand_selection(int *A, const int i, const int n, bool worst_case);