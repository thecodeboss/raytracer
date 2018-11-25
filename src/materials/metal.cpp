#include "materials/metal.h"
#include "math/utils.h"

Metal::Metal(const Vec3f &albedo) : albedo(albedo) {}

Metal::~Metal() {}

bool Metal::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                    Ray &scattered) const {
  Vec3f reflected = reflect(ray.direction, intersection.normal);
  scattered = Ray(intersection.point, reflected.normalize());
  attenuation = albedo;
  return scattered.direction.dot(intersection.normal) > 0;
}
