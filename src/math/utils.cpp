#include "math/utils.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <utility>

thread_local auto rand_double = std::bind(std::uniform_real_distribution<double>(0.0, 1.0),
                                          std::minstd_rand(std::random_device()()));

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

double drand() { return rand_double(); }

Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
  return (incident - 2 * incident.dot(normal) * normal).normalize();
}

bool refract(const Vec3f &incident, const Vec3f &normal, double ni_over_nt, Vec3f &refracted) {
  double dt = incident.dot(normal);
  double discr = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
  if (discr > 0.0) {
    refracted = (ni_over_nt * (incident - normal * dt) - normal * sqrt(discr)).normalize();
    return true;
  } else {
    return false;
  }
}

double schlick(double cosine, double refractive_index) {
  double r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
  r0 *= r0;
  return r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0);
}
