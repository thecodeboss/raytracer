#pragma once
#include "intersection.h"
#include "material.h"
#include "math/vector.h"
#include "ray.h"
#include <memory>

class Object {
public:
  Vec3f position;
  Material *material;

  Object();
  Object(const Vec3f &position);
  Object(const Vec3f &position, Material *material);
  virtual ~Object(){};

  virtual bool intersect(const Ray &ray, double t_min, double t_max,
                         Intersection &intersection) const = 0;
};
