#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
  int K = 10'000;
  double step_size = 0.5;

  srand((unsigned)time(NULL));

  double x = 0.0;
  int n_accept = 0;

  for (int k = 1; k < K + 1; k++) {
    // current
    double backup_x = x;
    double action_init = 0.5 * x * x;

    // proposal
    double dx = (double)rand() / RAND_MAX; // [0, 1]
    dx = (dx - 0.5) * step_size * 2.0; // [-0.5, 0.5]
    x = x + dx;
    double action_fin = 0.5 * x * x;

    // metro test
    double metro = (double)rand() / RAND_MAX;
    if (exp(action_init - action_fin) > metro)
      n_accept = n_accept + 1;
    else
      x = backup_x;

    printf("dx:%.10f, x:%.10f: acc_ratio:%f\n", dx, x, (double)n_accept / k);
  }
}