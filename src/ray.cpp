#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Vec3f &origin, const Vec3f &direction) : origin(origin), direction(direction) {}

Vec3f Ray::point_at(double t) const { return origin + t * direction; }
