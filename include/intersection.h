#pragma once
#include "math/vector.h"
#include <memory>

class Material;

class Intersection {
public:
  double t;
  Vec3f point;
  Vec3f normal;
  Material *material;

  Intersection();
  Intersection(double t, const Vec3f &point, const Vec3f &normal, Material *material);
};
