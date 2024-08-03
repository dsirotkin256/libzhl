#include "constants.hpp"
#include "gas_exchange.hpp"
#include <iostream>

/*

(A. A. Bühlmann, 1983, p. 14)

P_i(t_N) = P_i(t_0)  + [P_i.in- P_i(t_0)] x [1 - e^(-k x t_N)] or [1 -
e^(-0.69315 x t_N/2t)].

- P_i(t_N) is the pressure of the inert gas in the tissue at the end of the
exposure,
- P_i(t_0) is the pressure of the inert gas in the tissue at the beginning of
the exposure,
- P_i.in is the pressure of the inert gas in inspiration,
- e is the base of natural logarithms, 2.71828 ... ;
- k is the natural logarithm of 2, 0.69315, divided by the half-value time.
*/

// Function to calculate excess gas load (EGL)
double calculateEGL(double P, double P0, double t, double tau) {
  return (P - P0) * (1 - (t / tau));
}

// Function to calculate half-time (tau)
double calculateTau(double P, double P0) { return tau0 * (P / P0); }

// Function to calculate M-value (M)
double calculateM(double EGL, double tau) { return M0 * (1 - (EGL / tau)); }

// Function to calculate decompression stop (DS)
double calculateDS(double EGL, double M, double tau) {
  return (EGL / M) * (1 - (tau / tau0));
}

// Function to calculate gradient factor (GF)
double calculateGF(double M, double M0, double tau) {
  return (M / M0) * (1 - (tau0 / tau));
}

// Function to calculate decompression time (DT)
double calculateDT(double DS, double GF, double tau) {
  return (DS / GF) * (1 - (tau0 / tau));
}

// Main function
int main() {
  double P = 20.0;  // current pressure (bar)
  double P0 = 10.0; // initial pressure (bar)
  double t = 30.0;  // time (minutes)

  double tau = calculateTau(P, P0);
  double EGL = calculateEGL(P, P0, t, tau);
  double M = calculateM(EGL, tau);
  double DS = calculateDS(EGL, M, tau);
  double GF = calculateGF(M, M0, tau);
  double DT = calculateDT(DS, GF, tau);

  std::cout << "Excess gas load (EGL): " << EGL << " bar" << std::endl;
  std::cout << "Half-time (tau): " << tau << " minutes" << std::endl;
  std::cout << "M-value (M): " << M << " bar" << std::endl;
  std::cout << "Decompression stop (DS): " << DS << " minutes" << std::endl;
  std::cout << "Gradient factor (GF): " << GF << std::endl;
  std::cout << "Decompression time (DT): " << DT << " minutes" << std::endl;

  return 0;
}