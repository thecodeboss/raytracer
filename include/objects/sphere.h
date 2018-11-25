#pragma once
#include "math/vector.h"
#include "object.h"

class Sphere : public Object {
public:
  double radius, radius2;

  Sphere();
  Sphere(const Vec3f &position);
  Sphere(const Vec3f &position, double radius);

  virtual bool intersect(const Ray &ray, double t_min, double t_max,
                         Intersection &intersection) const override;
};
