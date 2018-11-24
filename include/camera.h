#pragma once
#include "math/matrix.h"
#include "math/vector.h"

class Camera {
public:
  Matrix44f camera_to_world;

  Camera();
  Camera(const Vec3f &position);
  Camera(const Vec3f &position, const Vec3f &look_at);

  void look_at(const Vec3f &look_at);
  Vec3f position() const;
};
