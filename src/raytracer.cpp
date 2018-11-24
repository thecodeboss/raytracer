#include "camera.h"
#include "image.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "ray.h"
#include <cinttypes>
#include <cmath>
#include <iostream>

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  Camera camera(Vec3f(-5.0, 2.0, 0.0));
  camera.look_at(Vec3f(0.0, 0.0, 0.0));

  Image image(600, 400);
  double scale = tan(camera.fov / 2);
  double aspect_ratio = double(image.x) / image.y;

  for (int i = 0; i < image.y; i++) {
    for (int j = 0; j < image.x; j++) {
      double x = (2 * (j + 0.5) / double(image.x) - 1) * aspect_ratio * scale;
      double y = (1 - 2 * (i + 0.5) / double(image.y)) * scale;
      Vec3f direction = camera.camera_to_world.multiply_dir(Vec3f(x, y, -1));
      Ray ray(camera.position(), direction);

      double r = double(j) / double(image.x);
      double g = double(i) / double(image.y);
      double b = 0.25;
      uint8_t ir = uint8_t(255.99 * r);
      uint8_t ig = uint8_t(255.99 * g);
      uint8_t ib = uint8_t(255.99 * b);
      image[i][j] = {ir, ig, ib};
    }
  }
  image.to_ppm("test.ppm");
  return 0;
}
