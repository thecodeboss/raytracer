#pragma once
#include "math/vector.h"

class Ray {
public:
  Vec3f origin, direction;

  Ray(const Vec3f &origin, const Vec3f &direction);
  Vec3f point_at(double t) const;
};
