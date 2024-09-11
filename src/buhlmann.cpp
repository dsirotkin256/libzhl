#include "constants.hpp"
#include <cmath>
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
auto calculateEGL(const double P, const double P0, const double t, double tau) {
  return (P - P0) * (1 - (t / tau));
}

// Function to calculate half-time (tau)
auto calculateTau(const double P, const double P0) { return tau0 * (P / P0); }

// Function to calculate M-value (M)
auto calculateM(const double EGL, const double tau) {
  return M0 * (1 - (EGL / tau));
}

// Function to calculate decompression stop (DS)
auto calculateDS(const double EGL, const double M, const double tau) {
  return (EGL / M) * (1 - (tau / tau0));
}

// Function to calculate gradient factor (GF)
auto calculateGF(const double M, const double tau) {
  return (M / M0) * (1 - (tau0 / tau));
}

// Function to calculate decompression time (DT)
auto calculateDT(const double DS, const double GF, const double tau) {
  return (DS / GF) * (1 - (tau0 / tau));
}

// Main function
int main() {
  const pressure_t P = 20.0;  // current pressure (bar)
  const pressure_t P0 = 10.0; // initial pressure (bar)
  const double_t t = 30.0;    // time (minutes)

  const double tau = calculateTau(P, P0);
  const double EGL = calculateEGL(P, P0, t, tau);
  const double M = calculateM(EGL, tau);
  const double DS = calculateDS(EGL, M, tau);
  const double GF = calculateGF(M, tau);
  const double DT = calculateDT(DS, GF, tau);

  std::cout << "Excess gas load (EGL): " << EGL << " bar" << std::endl;
  std::cout << "Half-time (tau): " << tau << " minutes" << std::endl;
  std::cout << "M-value (M): " << M << " bar" << std::endl;
  std::cout << "Decompression stop (DS): " << DS << " minutes" << std::endl;
  std::cout << "Gradient factor (GF): " << GF << std::endl;
  std::cout << "Decompression time (DT): " << DT << " minutes" << std::endl;

  return 0;
}