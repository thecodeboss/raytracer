#pragma once
#include "material.h"
#include "math/vector.h"

class DiffuseLight : public Material {
public:
  Vec3f emit;

  DiffuseLight(const Vec3f &emit);
  virtual ~DiffuseLight() override;

  virtual bool scatter(const Ray &ray, const Intersection &intersection, Vec3f &attenuation,
                       Ray &scattered) const override;
  virtual Vec3f emitted() const override;
};
