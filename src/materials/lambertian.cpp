#include "materials/lambertian.h"
#include <random>

Vec3f random_in_unit_sphere() {
  Vec3f point;
  std::default_random_engine re;
  std::uniform_real_distribution<double> uniform(0.0, 1.0);
  do {
    point = 2.0 * Vec3f(uniform(re), uniform(re), uniform(re)) - Vec3f(1.0, 1.0, 1.0);
  } while (point.norm() >= 1.0);

  return point;
}

Lambertian::Lambertian(const Vec3f &albedo) : albedo(albedo) {}

bool Lambertian::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                         Ray &scattered) const {
  (void)ray;
  Vec3f target = intersection.point + intersection.normal + random_in_unit_sphere();
  scattered = Ray(intersection.point, (target - intersection.point).normalize());
  attenuation = albedo;
  return true;
}
