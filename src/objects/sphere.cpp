#include "objects/sphere.h"
#include "math/utils.h"
#include <utility>

Sphere::Sphere() : Sphere(Vec3f(0, 0, 0), 1.0) {}

Sphere::Sphere(const Vec3f &position) : Sphere(position, 1.0) {}

Sphere::Sphere(const Vec3f &position, double radius)
    : Object(position), radius(radius), radius2(radius * radius) {}

Sphere::~Sphere() {}

bool Sphere::intersect(const Ray &ray, double t_min, double t_max,
                       Intersection &intersection) const {
  double t0, t1;

  Vec3f L = ray.origin - position;
  double a = 1.0; // ray.direction.norm(); (we assume rays have their direction normalized)
  double b = 2 * ray.direction.dot(L);
  double c = L.norm() - radius2;

  if (!solve_quadratic(a, b, c, t0, t1)) {
    return false;
  }

  if (t0 > t1) {
    std::swap(t0, t1);
  }

  if (t0 < t_min) {
    // if t0 is negative, use t1 instead
    t0 = t1;

    if (t0 < t_min) {
      // both t0 and t1 are negative
      return false;
    }
  }

  if (t0 < t_min || t0 > t_max) {
    return false;
  }

  intersection.t = t0;
  intersection.point = ray.origin + t0 * ray.direction;
  // divide by sphere radius as a quick normalization shortcut and
  // pray nobody creates spheres of zero radius
  intersection.normal = (intersection.point - position) / radius;
  intersection.material = material;

  return true;
}
