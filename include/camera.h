#pragma once
#include "math/matrix.h"
#include "math/vector.h"
#include "ray.h"
#include <cmath>

class Camera {
private:
  Vec3f position;
  Vec3f forward, up, right;

public:
  Matrix44f camera_to_world;
  double aperture = 0.1;
  double distance_to_focus = 10.0;
  double fov = M_PI_4;

  Camera();
  Camera(const Vec3f &position);

  void look_at(const Vec3f &look_at);
  Vec3f get_position() const;
  void set_position(Vec3f &p);
  Ray get_ray(double x, double y) const;
};
