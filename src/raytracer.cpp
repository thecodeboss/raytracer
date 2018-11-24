#include "camera.h"
#include "image.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "object.h"
#include "objects/sphere.h"
#include "ray.h"
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

typedef std::unique_ptr<Object> ObjectPtr;
typedef std::vector<ObjectPtr> Objects;

const Color white(1.0, 1.0, 1.0);
const Color light_blue(0.5, 0.7, 1.0);
const Color red(1.0, 0.0, 0.0);
const Color green(0.0, 1.0, 0.0);
const Color blue(0.0, 0.0, 1.0);

Color background(const Ray &ray) {
  double t = 0.5 * (ray.direction.y + 1.0);
  return (1.0 - t) * white + t * light_blue;
}

Color cast_ray(const Ray &ray, const Objects &objects) {
  Color result(0, 0, 0);
  double infinity = std::numeric_limits<double>::infinity();
  double closest_t = infinity;
  for (auto &object : objects) {
    double t;
    if (object->intersect(ray, t) && t < closest_t) {
      result = object->color;
      closest_t = t;
    }
  }

  if (closest_t == infinity) {
    return background(ray);
  } else {
    return result;
  }
}

void render(const Camera &camera, Image &image, const Objects &objects,
            const std::string &filename) {
  double scale = tan(camera.fov / 2);
  double aspect_ratio = double(image.x) / image.y;

  for (int i = 0; i < image.y; i++) {
    for (int j = 0; j < image.x; j++) {
      double x = (2 * (j + 0.5) / double(image.x) - 1) * aspect_ratio * scale;
      double y = (1 - 2 * (i + 0.5) / double(image.y)) * scale;
      Vec3f direction = camera.camera_to_world.multiply_dir(Vec3f(x, y, -1));
      Ray ray(camera.position(), direction);
      image[i][j] = cast_ray(ray, objects);
    }
  }
  image.to_ppm(filename);
}

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  Objects objects;
  objects.push_back(ObjectPtr(new Sphere(Vec3f(0.0, 0.0, 0.0))));
  objects[0]->color = red;

  objects.push_back(ObjectPtr(new Sphere(Vec3f(-2.0, 0.0, 0.6), 0.5)));
  objects[1]->color = green;

  objects.push_back(ObjectPtr(new Sphere(Vec3f(-2.0, 0.5, -0.5), 0.3)));
  objects[2]->color = blue;

  Camera camera(Vec3f(-5.0, 1.0, 0.0));
  camera.look_at(objects[0]->position);

  Image image(600, 400);

  render(camera, image, objects, "test.ppm");

  return 0;
}
