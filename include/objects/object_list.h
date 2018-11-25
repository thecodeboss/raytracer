#pragma once
#include "object.h"
#include <vector>

class ObjectList : public Object {
private:
  std::vector<Object *> objects;

public:
  ObjectList();
  virtual ~ObjectList() override;
  const Object *operator[](size_t i) const;
  Object *operator[](size_t i);
  auto begin() { return objects.begin(); }
  auto end() { return objects.end(); }

  virtual bool intersect(const Ray &ray, double t_min, double t_max,
                         Intersection &intersection) const override;
  void add(Object *object);
};
