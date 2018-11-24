#include "camera.h"
#include "image.h"
#include "math/matrix.h"
#include "math/vector.h"
#include <cinttypes>
#include <iostream>

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;
  // clang-format off
  Matrix44f test_matrix(
    1.1, 1.2, 1.3, 1.4,
    2.1, 2.2, 2.3, 2.4,
    3.1, 3.2, 3.3, 3.4,
    4.1, 4.2, 4.3,4.4
  );
  // clang-format on
  std::cout << test_matrix << std::endl;

  Vec3f test_vector(1, 2, 3);
  std::cout << test_vector << std::endl;
  std::cout << test_vector + test_vector << std::endl;
  std::cout << test_vector.dot(test_vector) << std::endl;
  std::cout << test_vector.cross(test_vector) << std::endl;
  std::cout << test_matrix.multiply_vec(test_vector) << std::endl;

  Camera camera(Vec3f(-5.0, 2.0, 0.0));
  camera.look_at(Vec3f(0.0, 0.0, 0.0));

  Image image(600, 400);
  for (int i = 0; i < image.y; i++) {
    for (int j = 0; j < image.x; j++) {
      float r = float(j) / float(image.x);
      float g = float(i) / float(image.y);
      float b = 0.25;
      uint8_t ir = uint8_t(255.99 * r);
      uint8_t ig = uint8_t(255.99 * g);
      uint8_t ib = uint8_t(255.99 * b);
      image[i][j] = {ir, ig, ib};
    }
  }
  image.to_ppm("test.ppm");
  return 0;
}
