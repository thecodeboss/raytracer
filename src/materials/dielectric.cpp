#include "materials/dielectric.h"
#include "math/utils.h"

Dielectric::Dielectric(double refractive_index) : refractive_index(refractive_index) {}

Dielectric::~Dielectric() {}

bool Dielectric::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                         Ray &scattered) const {
  double ni_over_nt, cosine, reflect_probability;
  Vec3f outward_normal, refracted;
  Vec3f reflected = reflect(ray.direction, intersection.normal);
  attenuation = Vec3f(1.0, 1.0, 1.0);

  if (ray.direction.dot(intersection.normal) > 0.0) {
    outward_normal = -intersection.normal;
    ni_over_nt = refractive_index;
    cosine = refractive_index * ray.direction.dot(intersection.normal);
  } else {
    outward_normal = intersection.normal;
    ni_over_nt = 1.0 / refractive_index;
    cosine = -ray.direction.dot(intersection.normal);
  }

  if (refract(ray.direction, outward_normal, ni_over_nt, refracted)) {
    reflect_probability = schlick(cosine, refractive_index);
  } else {
    reflect_probability = 1.0;
  }

  if (drand() < reflect_probability) {
    scattered = Ray(intersection.point, reflected);
  } else {
    scattered = Ray(intersection.point, refracted);
  }
  return true;
}
