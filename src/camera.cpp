#include "camera.h"
#include "math/matrix.h"
#include "math/utils.h"
#include "math/vector.h"
#include <iostream>

static Vec3f random_in_unit_disk() {
  Vec3f point;
  do {
    point = Vec3f(2.0 * drand() - 1, 2.0 * drand() - 1, 0.0);
  } while (point.norm() >= 1.0);

  return point;
}

Camera::Camera() : camera_to_world(Matrix44f()) {}

Camera::Camera(const Vec3f &position) : position(position) {
  right = Vec3f(1.0, 0.0, 0.0);
  up = Vec3f(0.0, 1.0, 0.0);
  forward = Vec3f(0.0, 0.0, 1.0);

  // clang-format off
  camera_to_world = Matrix44f(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    position.x, position.y, position.z, 0.0
  );
  // clang-format on
}

void Camera::look_at(const Vec3f &to) {
  distance_to_focus = (position - to).length();
  forward = (position - to).normalize();
  right = Vec3f(0, 1, 0).cross(forward);
  up = forward.cross(right);

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

Ray Camera::get_ray(double x, double y) const {
  double lens_radius = aperture / 2.0;
  Vec3f rd = lens_radius * random_in_unit_disk();
  Vec3f pos_offset = right * rd.x + up * rd.y;

  Vec3f orig_ray_direction = camera_to_world.multiply_dir(Vec3f(x, y, -1)).normalize();
  Vec3f dir_offset =
      (distance_to_focus * orig_ray_direction - pos_offset).normalize() - orig_ray_direction;

  return Ray(position + pos_offset, (orig_ray_direction + dir_offset).normalize());
}
