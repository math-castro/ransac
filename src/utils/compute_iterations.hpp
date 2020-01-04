#include "utils/compute_iterations.hpp"

#include <cmath>

int compute_iterations(double p, double r, int s) {
  const int INF = 0x3f3f3f3f;
  if(fabs(r) < 1e-9) return INF;
  return ceil(log(1-p)/log(1-pow(r,s)))+1e-9;
}