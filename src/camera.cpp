#include "camera.h"
#include "math/matrix.h"
#include "math/vector.h"
#include <iostream>

Camera::Camera() : camera_to_world(Matrix44f()) {}

Camera::Camera(const Vec3f &position) : position(position) {
  // clang-format off
  camera_to_world = Matrix44f(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    position.x, position.y, position.z, 0.0
  );
  // clang-format on
}

Camera::Camera(const Vec3f &position, const Vec3f &look_at) : Camera(position) {
  this->look_at(look_at);
}

void Camera::look_at(const Vec3f &to) {
  Vec3f forward = (position - to).normalize();
  Vec3f right = Vec3f(0, 1, 0).cross(forward);
  Vec3f up = forward.cross(right);

  camera_to_world[0][0] = right.x;
  camera_to_world[0][1] = right.y;
  camera_to_world[0][2] = right.z;
  camera_to_world[1][0] = up.x;
  camera_to_world[1][1] = up.y;
  camera_to_world[1][2] = up.z;
  camera_to_world[2][0] = forward.x;
  camera_to_world[2][1] = forward.y;
  camera_to_world[2][2] = forward.z;
}

Vec3f Camera::get_position() const { return position; }

void Camera::set_position(Vec3f &p) {
  position = p;
  camera_to_world[3][0] = p.x;
  camera_to_world[3][1] = p.y;
  camera_to_world[3][2] = p.z;
}
