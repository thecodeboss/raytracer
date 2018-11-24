#pragma once
#include "intersection.h"
#include "ray.h"

class Material {
public:
  Material() {}

  virtual bool scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                       Ray &scattered) const = 0;
};
