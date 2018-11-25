#pragma once
#include "material.h"
#include "math/vector.h"

class Dielectric : public Material {
public:
  double refractive_index;

  Dielectric(double refractive_index);
  virtual ~Dielectric() override;

  virtual bool scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                       Ray &scattered) const override;
};
