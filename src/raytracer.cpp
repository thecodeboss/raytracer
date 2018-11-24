#include "camera.h"
#include "image.h"
#include "intersection.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "object.h"
#include "objects/object_list.h"
#include "objects/sphere.h"
#include "ray.h"
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

const Color white(1.0, 1.0, 1.0);
const Color black(0.0, 0.0, 0.0);
const Color light_blue(0.5, 0.7, 1.0);
const double infinity = std::numeric_limits<double>::infinity();

Color background(const Ray &ray) {
  double t = 0.5 * (ray.direction.y + 1.0);
  return (1.0 - t) * white + t * light_blue;
}

Color cast_ray(const Ray &ray, Object *world, int depth) {
  Intersection intersection;
  if (world->intersect(ray, 0.001, infinity, intersection)) {
    Ray scattered;
    Vec3f attenuation;
    if (depth < 5 && intersection.material->scatter(ray, intersection, attenuation, scattered)) {
      return attenuation * cast_ray(scattered, world, depth + 1);
    } else {
      return black;
    }
  } else {
    return background(ray);
  }
}

void render(const Camera &camera, Image &image, Object *world, const std::string &filename) {
  double scale = tan(camera.fov / 2);
  double aspect_ratio = double(image.x) / image.y;

  for (int i = 0; i < image.y; i++) {
    for (int j = 0; j < image.x; j++) {
      double x = (2 * (j + 0.5) / double(image.x) - 1) * aspect_ratio * scale;
      double y = (1 - 2 * (i + 0.5) / double(image.y)) * scale;
      Vec3f direction = camera.camera_to_world.multiply_dir(Vec3f(x, y, -1));
      Ray ray(camera.position(), direction);
      image[i][j] = cast_ray(ray, world, 0);
    }
  }
  image.to_ppm(filename);
}

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  ObjectList objects;
  objects.add(new Sphere(Vec3f(0.0, 1.0, 0.0)));
  objects.add(new Sphere(Vec3f(-2.0, 0.5, 0.6), 0.5));
  objects.add(new Sphere(Vec3f(0.0, -1000.0, 0.0), 1000.0));

  Camera camera(Vec3f(-10.0, 1.0, 0.0));
  camera.look_at(objects[0]->position);

  Image image(600, 400);

  render(camera, image, &objects, "test.ppm");

  return 0;
}
