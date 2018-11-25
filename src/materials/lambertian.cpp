#include "materials/lambertian.h"
#include "math/utils.h"

Vec3f random_in_unit_sphere() {
  Vec3f point;
  do {
    point = Vec3f(2.0 * drand() - 1, 2.0 * drand() - 1, 2.0 * drand() - 1);
  } while (point.norm() >= 1.0);

  return point;
}

Lambertian::Lambertian(const Vec3f &albedo) : albedo(albedo) {}

Lambertian::~Lambertian() {}

bool Lambertian::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                         Ray &scattered) const {
  (void)ray;
  Vec3f target = intersection.point + intersection.normal + random_in_unit_sphere();
  scattered = Ray(intersection.point, (target - intersection.point).normalize());
  attenuation = albedo;
  return true;
}
