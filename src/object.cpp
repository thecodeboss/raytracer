#include "object.h"
#include "math/vector.h"

Object::Object() : Object(Vec3f(0.0, 0.0, 0.0)) {}

Object::Object(const Vec3f &position) : Object(position, Color(0.0, 0.0, 0.0)) {}

Object::Object(const Vec3f &position, const Color &color) : position(position), color(color) {}
