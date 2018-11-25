#include "math/utils.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <random>
#include <utility>

static std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
static std::uniform_real_distribution<double> uniform(0.0, 1.0);
static auto rand_double = std::bind(uniform, re);

static double rand_doubles[65536];
static int idx = 0;
static bool do_random_init() {
  for (int i = 0; i < 65536; i++) {
    rand_doubles[i] = rand_double();
  }
  return true;
}
static bool init = do_random_init();

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

double drand() { return rand_doubles[idx++ % 65536]; }
