#pragma once
#include "math/vector.h"
#include "object.h"

class Sphere : public Object {
public:
  double radius2;

  Sphere();
  Sphere(const Vec3f &position);
  Sphere(const Vec3f &position, double radius);

  virtual bool intersect(const Ray &ray, double &t) const override;
};
