#include "objects/object_list.h"

const double infinity = std::numeric_limits<double>::infinity();

ObjectList::ObjectList() {}

const Object *ObjectList::operator[](size_t i) const { return objects[i]; }
Object *ObjectList::operator[](size_t i) { return objects[i]; }

bool ObjectList::intersect(const Ray &ray, double t_min, double t_max,
                           Intersection &intersection) const {
  Intersection tmp_intersection;
  bool hit_anything = false;
  double t_closest = t_max;

  for (auto &object : objects) {
    if (object->intersect(ray, t_min, t_closest, tmp_intersection)) {
      hit_anything = true;
      t_closest = tmp_intersection.t;
      intersection = tmp_intersection;
    }
  }

  return hit_anything;
}

void ObjectList::add(Object *object) { objects.push_back(object); }
