#include "materials/diffuse_light.h"
#include "math/utils.h"

DiffuseLight::DiffuseLight(const Vec3f &emit) : emit(emit) {}

DiffuseLight::~DiffuseLight() {}

bool DiffuseLight::scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                           Ray &scattered) const {
  (void)ray;
  (void)intersection;
  (void)attenuation;
  (void)scattered;
  return false;
}

Vec3f DiffuseLight::emitted() const { return emit; }
