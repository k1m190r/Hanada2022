#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

const int K = 10'000;
const int n_tau = 40;
const double d_tau = 1.0;

void box_miller(double& p, double& q) {
  double pi = 2.0 * asin(1.0);

  double r = (double)rand() / RAND_MAX;
  double s = (double)rand() / RAND_MAX;

  p = sqrt(-2.0 * log(r)) * sin(2.0 * pi * s);
  q = sqrt(-2.0 * log(r)) * cos(2.0 * pi * s);
}

double action(const double x) { return 0.5 * x * x; }

double hamiltonian(const double x, const double p) {
  double ham = action(x);
  return ham + 0.5 * p * p;
}

double del_h(const double x) { return x; }

void MD(double& x, double& init, double& fin) {
  double r1, r2;
  box_miller(r1, r2);

  double p = r1;

  init = hamiltonian(x, p);
  x = x + p * 0.5 * d_tau;
  for (int k = 1; k != n_tau; k++) {
    double _del_h = del_h(x);
    p = p - _del_h * d_tau;
    x = x + p * d_tau;
  }

  double _del_h = del_h(x);
  p = p - _del_h * d_tau;
  x = x + p * 0.5 * d_tau;

  fin = hamiltonian(x, p);
}

int main() {
  srand((unsigned)time(NULL));

  double x = 0.0;

  std::ofstream out_file("output.txt");

  int n_accept = 0;
  double sum_xx = 0.0;

  for (int k = 0; k != K; k++) {
    double _x = x;
    double init, fin;
    MD(x, init, fin);
    double metro = (double)rand() / RAND_MAX;
    if (exp(init - fin) > metro)
      n_accept += 1;
    else
      x = _x;

    std::cout << std::fixed << std::setprecision(6)
        << x << "  " 
        << sum_xx/((double) (k+1)) << "  "
        << ((double) n_accept/((double) k+1))
        << std::endl;

    out_file << std::fixed << std::setprecision(6)
        << x << "  " 
        << sum_xx/((double) (k+1)) << "  "
        << ((double) n_accept/((double) k+1))
        << std::endl;

  }

  out_file.close();
}