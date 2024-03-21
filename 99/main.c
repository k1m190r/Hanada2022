#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int niter = 1'000;
  srand((unsigned)time(NULL));

  int n_in = 0;
  for (int iter = 1; iter < niter + 1; iter++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;

    if (x * x + y * y < 1e0) n_in += 1;
    printf("%.10f\n", (double)n_in / iter);
  }
}