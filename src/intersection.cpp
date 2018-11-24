#include "intersection.h"
#include "math/vector.h"

Intersection::Intersection() {}

Intersection::Intersection(double t, const Vec3f &point, const Vec3f &normal, Material *material)
    : t(t), point(point), normal(normal), material(material) {}
