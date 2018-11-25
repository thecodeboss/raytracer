#pragma once
#include "math/vector.h"
#include <cinttypes>
#include <mutex>
#include <string>

class Image {
private:
  Color *buffer;
  std::mutex *mutexes;

public:
  uint16_t x, y;

  Image(uint16_t xx, uint16_t yy);
  ~Image();
  const Color *operator[](uint16_t i) const;
  Color *operator[](uint16_t i);

  // Needed so multiple threads can write to the same image simultaneously
  void safe_add(uint16_t i, uint16_t j, const Color &color);

  bool to_ppm(const std::string &filename) const;
};
