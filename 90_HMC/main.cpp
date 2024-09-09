#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <tuple>

const int K = 100'000;
const int n_tau = 10;
const double d_tau = 0.1;

std::tuple<double, double> box_miller() {
  double pi = 2.0 * asin(1.0);

  double p = (double)rand() / RAND_MAX;
  double q = (double)rand() / RAND_MAX;

  double x = sqrt(-2.0 * log(p)) * cos(2.0 * pi * q);
  double y = sqrt(-2.0 * log(p)) * sin(2.0 * pi * q);

  return std::make_tuple(x, y);
}

double action(const double x) { return 0.5 * x * x; }

double hamiltonian(const double x, const double p) {
  double ham = action(x);
  return ham + 0.5 * p * p;
}

double del_h(const double x) { return x; }

std::tuple<double, double> 
MD(double &x) {
  auto [p, _]  = box_miller();

  auto init = hamiltonian(x, p);
  x = x + p * 0.5 * d_tau;

  for (int k = 1; k != n_tau; k++) {
    auto _del_h = del_h(x);
    p = p - _del_h * d_tau;
    x = x + p * d_tau;
  }

  auto _del_h = del_h(x);
  p = p - _del_h * d_tau;
  x = x + p * 0.5 * d_tau;

  auto fin = hamiltonian(x, p);

  return std::make_tuple(init, fin);
}

int main() {
  srand((unsigned)time(NULL));

  double x = 0.0;

  std::ofstream out_file("output.txt");

  int n_accept = 0;
  double sum_xx = 0.0;

  for (int k = 0; k != K; k++) {
    double _x = x;
    auto [init, fin] = MD(x);
    double metro = (double)rand() / RAND_MAX;
    if (exp(init - fin) > metro)
      n_accept += 1;
    else
      x = _x;

    sum_xx += x * x;

    if (k % 10'000 == 0) {
      std::cout << k << "  " << std::fixed << std::setprecision(6) << x << "  "
                << sum_xx / ((double)(k + 1)) << "  "
                << ((double)n_accept / ((double)k + 1)) << std::endl;

      out_file << k << "  " << std::fixed << std::setprecision(6) << x << "  "
               << sum_xx / ((double)(k + 1)) << "  "
               << ((double)n_accept / ((double)k + 1)) << std::endl;
    }
  }

  out_file.close();
}