#include "math/matrix.h"
#include "math/vector.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;
  Matrix44f testMatrix(1.1, 1.2, 1.3, 1.4, 2.1, 2.2, 2.3, 2.4, 3.1, 3.2, 3.3, 3.4, 4.1, 4.2, 4.3,
                       4.4);
  std::cout << testMatrix << std::endl;

  Vec3f testVector(1, 2, 3);
  std::cout << testVector << std::endl;
  std::cout << testVector + testVector << std::endl;
  std::cout << testVector.dot(testVector) << std::endl;
  std::cout << testVector.cross(testVector) << std::endl;
  std::cout << testMatrix.multiplyVec(testVector) << std::endl;
  return 0;
}
