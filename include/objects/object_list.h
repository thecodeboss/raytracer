#pragma once
#include "object.h"
#include <vector>

class ObjectList : public Object {
private:
  std::vector<Object *> objects;

public:
  ObjectList();
  const Object *operator[](size_t i) const;
  Object *operator[](size_t i);

  virtual bool intersect(const Ray &ray, double t_min, double t_max,
                         Intersection &intersection) const override;
  void add(Object *object);
};
