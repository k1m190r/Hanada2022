#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

const int K = 1'000;
const int n_tau = 20;
const double d_tau = 0.5;
const int Nd = 3;

void box_muller(double& p, double& q) {
  double pi = 2.0 * asin(1.0);

  double r = (double)rand() / RAND_MAX;
  double s = (double)rand() / RAND_MAX;

  p = sqrt(-2.0 * log(r)) * sin(2.0 * pi * s);
  q = sqrt(-2.0 * log(r)) * cos(2.0 * pi * s);
}

double action(
  const double x[Nd], 
  const double A[Nd][Nd]) {

  double act = 0.0;
  for (int i = 0; i != Nd; i++) {
    for (int j = 0; j != i; j++) 
      act += x[i] * A[i][j] * x[j];
    act += 0.5 * x[i] * A[i][i] * x[i];
  }
  return act;
}

double hamilton(
  const double x[Nd],
  const double p[Nd],
  const double A[Nd][Nd]) {

  double ham = action(x, A);
  for (int i = 0; i != Nd; i++)
    ham += 0.5 * p[i] * p[i];
  return ham;
}

void del_h(
  const double x[Nd],
  const double A[Nd][Nd],
  double (&delh)[Nd]) {

  for (int i = 0; i != Nd; i++)
    delh[i] = 0.0;
  for (int i = 0; i != Nd; i++)
    for (int j = 0; j != Nd; j++)
      delh[i] += A[i][j] * x[j];
}

void MD(
  double (&x)[Nd],
  const double A[Nd][Nd],
  double& init,
  double& fin) {

  double p[Nd];
  double delh[Nd];
  double r1, r2;

  for (int i = 0; i != Nd; i++) {
    box_muller(r1, r2);
    p[i] = r1;
  }

  init = hamilton(x, p, A);
  for (int i = 0; i != Nd; i++)
    x[i] += p[i] * 0.5 * d_tau;

  for (int s = 0; s != n_tau; s++) {
    del_h(x, A, delh);
    for (int i = 0; i != Nd; i++)
      p[i] -= delh[i] * d_tau;
    for (int i = 0; i != Nd; i++)
      x[i] += p[i] * d_tau;
  }

  del_h(x, A, delh);
  for (int i = 0; i != Nd; i++)
    p[i] -= delh[i] * d_tau;
  for (int i = 0; i != Nd; i++)
    x[i] += p[i] * 0.5 * d_tau;

  fin = hamilton(x, p, A);
}

int main() {
  double x[Nd];
  double A[Nd][Nd];

  A[0][0] = 1.0;
  A[1][1] = 2.0;
  A[2][2] = 2.0;

  A[0][1] = 1.0;
  A[0][2] = 1.0;
  A[1][2] = 1.0;

  for (int i = 1; i != Nd; i++)
    for (int j = 0; j != i; j++)
      A[i][j] = A[j][i];

  srand((unsigned)time(NULL));

  for (int i = 0; i != Nd; i++)
    x[i] = 0.0;

  std::ofstream output_file("output.txt");

  int n_accept = 0;

  for (int k = 0; k != K; k++) {
    double x_[Nd];
    for (int i = 0; i != Nd; i++)
      x_[i] = x[i];

    double init, fin;
    MD(x, A, init, fin);

    double metro = (double)rand() / RAND_MAX;
    if (exp(init - fin) > metro)
      n_accept += 1;
    else
      for (int i = 0; i != Nd; i++)
        x[i] = x_[i];

    if ((k + 1) % 100 == 0) {
      std::cout << std::fixed
        << std::setprecision(6) 
        << x[0] << "   "
        << x[1] << "   "
        << x[2] << "   "
        << ((double)n_accept) / ((double)k + 1)
        << std::endl;

      output_file << std::fixed
        << std::setprecision(6)
        << x[0] << "   "
        << x[1] << "   "
        << x[2] << "   "
        << ((double)n_accept) / ((double)k + 1)
        << std::endl;
    }
  }
  output_file.close();
}