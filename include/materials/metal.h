#pragma once
#include "material.h"
#include "math/vector.h"

class Metal : public Material {
public:
  Vec3f albedo;

  Metal(const Vec3f &albedo);
  virtual ~Metal() override;

  virtual bool scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                       Ray &scattered) const override;
};
