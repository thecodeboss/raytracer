#pragma once
#include "math/matrix.h"
#include "math/vector.h"
#include "ray.h"
#include <cmath>

class Camera {
private:
  Vec3f position;

public:
  Matrix44f camera_to_world;
  double fov = M_PI_4;

  Camera();
  Camera(const Vec3f &position);
  Camera(const Vec3f &position, const Vec3f &look_at);

  void look_at(const Vec3f &look_at);
  Vec3f get_position() const;
  void set_position(Vec3f &p);
  Ray get_ray(double x, double y) const;
};
