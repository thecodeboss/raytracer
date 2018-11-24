#include "object.h"
#include "math/vector.h"

Object::Object() : Object(Vec3f(0.0, 0.0, 0.0)) {}

Object::Object(const Vec3f &position) : position(position) {}
