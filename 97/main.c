#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
  int K = 10'000;
  srand((unsigned)time(NULL));

  double pi = asin(1.0) * 2.0;
  double sum_z = 0.0;
  int n_in = 0;

  for (int k = 1; k < K + 1; k++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;

    if (x * x + y * y < 1.0) {
      n_in += 1;
      double z = sqrt(1.0 - x * x - y * y);
      sum_z += z;
    }

    printf("%d: %.10f\n", k, sum_z / n_in * 2.0 * pi);
  }
}