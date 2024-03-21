#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
  int niter = 1000;
  srand((unsigned)time(NULL));

  double sum_y = 0.0;
  for (int iter = 1; iter < niter + 1; iter++) {
    double x = (double)rand() / RAND_MAX;
    double y = sqrt(1e0 - x * x);
    sum_y += y;
    printf("%.10f\n", sum_y / iter);
  }
}