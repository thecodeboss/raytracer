#pragma once
#include "math/vector.h"
#include "ray.h"

class Object {
public:
  Vec3f position;
  Color color;

  Object();
  Object(const Vec3f &position);
  Object(const Vec3f &position, const Color &color);

  virtual bool intersect(const Ray &ray, double &t) const = 0;
};
