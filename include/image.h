#pragma once
#include "math/vector.h"
#include <cinttypes>
#include <string>

typedef Vec3<uint8_t> Color;

class Image {
private:
  Color *buffer;

public:
  uint16_t x, y;

  Image(uint16_t xx, uint16_t yy);
  ~Image();
  const Color *operator[](uint16_t i) const;
  Color *operator[](uint16_t i);

  bool to_ppm(const std::string &filename) const;
};
