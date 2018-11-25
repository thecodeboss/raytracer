#include "camera.h"
#include "image.h"
#include "intersection.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "math/matrix.h"
#include "math/utils.h"
#include "math/vector.h"
#include "object.h"
#include "objects/object_list.h"
#include "objects/sphere.h"
#include "ray.h"
#include "thread_pool.h"
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
    if (depth < 10 && intersection.material->scatter(ray, intersection, attenuation, scattered)) {
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
#ifdef DEBUG
  const int num_samples = 100;
#else
  const int num_samples = 800;
#endif

  ThreadPool thread_pool;

  for (int s = 0; s < num_samples; s++) {
    thread_pool.add_task([&]() -> void {
      for (int i = 0; i < image.y; i++) {
        for (int j = 0; j < image.x; j++) {
          double x = (2 * (j + drand()) / double(image.x) - 1) * aspect_ratio * scale;
          double y = (1 - 2 * (i + drand()) / double(image.y)) * scale;
          Ray ray = camera.get_ray(x, y);
          Color color = cast_ray(ray, world, 0);
          image.safe_add(i, j, color);
        }
      }
    });
  }

  thread_pool.wait_all();

  for (int i = 0; i < image.y; i++) {
    for (int j = 0; j < image.x; j++) {
      image[i][j] /= double(num_samples);
      image[i][j] = sqrt(image[i][j]);
    }
  }

  image.to_ppm(filename);
}

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  ObjectList objects;
  objects.add(new Sphere(Vec3f(0.0, 1.0, 0.0)));
  objects.add(new Sphere(Vec3f(-2.0, 0.5, 0.9), 0.5));
  objects.add(new Sphere(Vec3f(-1.5, 0.7, -2.0), 0.7));
  objects.add(new Sphere(Vec3f(-0.5, 0.8, 2.5), 0.8));
  objects.add(new Sphere(Vec3f(1.1, 1.0, -1.9), 1.0));
  objects.add(new Sphere(Vec3f(-1.7, 0.4, -0.7), 0.4));
  objects.add(new Sphere(Vec3f(0.0, -1000.0, 0.0), 1000.0));

  Material *diffuse_green = new Lambertian(Vec3f(0.3, 0.8, 0.3));
  Material *diffuse_pink = new Lambertian(Vec3f(0.8, 0.3, 0.3));
  Material *metallic_red = new Metal(Vec3f(0.8, 0.2, 0.2));
  Material *metallic_blue = new Metal(Vec3f(0.2, 0.2, 0.8));
  Material *stainless_steel = new Metal(Vec3f(0.8, 0.8, 0.8));
  Material *glass = new Dielectric(1.5);

  objects[0]->material = diffuse_green;
  objects[1]->material = diffuse_pink;
  objects[2]->material = metallic_red;
  objects[3]->material = metallic_blue;
  objects[4]->material = stainless_steel;
  objects[5]->material = glass;

  Image image(600, 400);

  Camera camera(Vec3f(-7.0, 2.0, 0.0));
  camera.look_at(Vec3f(0.0, 0.4, 0.0));
  camera.aperture = 0.3;
  camera.fov = deg2rad(30);

  render(camera, image, &objects, "test.ppm");

  delete diffuse_green;
  delete diffuse_pink;
  delete metallic_red;
  delete metallic_blue;
  delete stainless_steel;
  delete glass;
  for (auto object : objects) {
    delete object;
  }
  return 0;
}
