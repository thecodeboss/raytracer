#include "objects/sphere.h"
#include "math/utils.h"
#include <utility>

Sphere::Sphere() : Sphere(Vec3f(0, 0, 0), 1.0) {}

Sphere::Sphere(const Vec3f &position) : Sphere(position, 1.0) {}

Sphere::Sphere(const Vec3f &position, double radius) : Object(position), radius2(radius * radius) {}

bool Sphere::intersect(const Ray &ray, double &t) const {
  double t0, t1;

  Vec3f L = ray.origin - position;
  double a = ray.direction.norm();
  double b = 2 * ray.direction.dot(L);
  double c = L.norm() - radius2;

  if (!solve_quadratic(a, b, c, t0, t1)) {
    return false;
  }

  if (t0 > t1) {
    std::swap(t0, t1);
  }

  if (t0 < 0) {
    // if t0 is negative, use t1 instead
    t0 = t1;

    if (t0 < 0) {
      // both t0 and t1 are negative
      return false;
    }
  }

  t = t0;

  return true;
}
