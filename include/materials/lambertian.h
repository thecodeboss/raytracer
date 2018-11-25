#pragma once
#include "material.h"
#include "math/vector.h"

class Lambertian : public Material {
public:
  Vec3f albedo;

  Lambertian(const Vec3f &albedo);
  virtual ~Lambertian() override;

  virtual bool scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                       Ray &scattered) const override;
};
