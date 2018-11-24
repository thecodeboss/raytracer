#pragma once
#include "math/vector.h"
#include "ray.h"

class Object {
public:
  Vec3f position;

  Object();
  Object(const Vec3f &position);

  virtual bool intersect(const Ray &ray, double &t) const = 0;
};
