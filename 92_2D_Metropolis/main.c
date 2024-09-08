#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
  int K = 100'000;
  double step_x = 0.5;
  double step_y = 0.5;

  srand((unsigned)time(NULL));
  double x = 0.0;
  double y = 0.0;

  int n_accept = 0;

  for (int k = 1; k < K + 1; k++) {
    double _x = x;
    double _y = y;
    double init = 0.5 * (x * x + y * x + y * y);

    double dx = (double)rand() / RAND_MAX;
    double dy = (double)rand() / RAND_MAX;

    dx = (dx - 0.5) * step_x * 2.0;
    dy = (dy - 0.5) * step_y * 2.0;

    x = x + dx;
    y = y + dy;

    double fin = 0.5 * (x * x + y * x + y * y);

    double metro = (double)rand() / RAND_MAX;
    bool cond = exp(init - fin) > metro;
    if (cond)
      n_accept += 1;
    else {
      x = _x;
      y = _y;
    }

    if (k % 1000 == 0) {
      printf("%8d: %.10f   %.10f    %f\n", k, x, y, (double)n_accept / k);
    }
  }
}