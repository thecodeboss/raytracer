#include "materials/metal.h"
#include "math/utils.h"

static Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
  return incident - 2 * incident.dot(normal) * normal;
}

Metal::Metal(const Vec3f &albedo) : albedo(albedo) {}

Metal::~Metal() {}

bool Metal::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                    Ray &scattered) const {
  Vec3f reflected = reflect(ray.direction, intersection.normal);
  scattered = Ray(intersection.point, reflected.normalize());
  attenuation = albedo;
  return scattered.direction.dot(intersection.normal) > 0;
}
