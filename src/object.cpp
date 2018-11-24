#include "object.h"
#include "materials/lambertian.h"
#include "math/vector.h"

static Lambertian default_material(Vec3f(0.8, 0.3, 0.3));

Object::Object() : Object(Vec3f(0.0, 0.0, 0.0)) {}

Object::Object(const Vec3f &position) : Object(position, &default_material) {}

Object::Object(const Vec3f &position, Material *material)
    : position(position), material(material) {}
