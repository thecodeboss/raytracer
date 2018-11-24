#include "math/utils.h"
#include <algorithm>
#include <cmath>
#include <utility>

double clamp(double lo, double hi, double v) { return std::max(lo, std::min(hi, v)); }

bool solve_quadratic(double a, double b, double c, double &x0, double &x1) {
  double discr = b * b - 4 * a * c;

  if (discr < 0) {
    return false;
  } else if (discr == 0) {
    x0 = x1 = -0.5 * b / a;
  } else {
    double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }

  if (x0 > x1) {
    std::swap(x0, x1);
  }

  return true;
}
