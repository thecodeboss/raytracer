#include "image.h"
#include "math/utils.h"
#include <cinttypes>
#include <fstream>
#include <iomanip>
#include <iostream>

Image::Image(uint16_t xx, uint16_t yy) : x(xx), y(yy) {
  buffer = new Color[x * y];
  mutexes = new std::mutex[x * y];
  for (int i = 0; i < x * y; i++) {
    buffer[i] = {0, 0, 0};
  }
}

Image::~Image() {
  delete[] buffer;
  delete[] mutexes;
}

const Color *Image::operator[](uint16_t i) const { return &buffer[i * x]; }

Color *Image::operator[](uint16_t i) { return &buffer[i * x]; }

void Image::safe_add(uint16_t i, uint16_t j, const Color &color) {
  mutexes[i * x + j].lock();
  buffer[i * x + j] += color;
  mutexes[i * x + j].unlock();
}

bool Image::to_ppm(const std::string &filename) const {
  std::ofstream file;
  file.open(filename);
  file.setf(std::ios_base::fixed);
  if (file.is_open()) {
    file << "P6\n" << x << " " << y << " 255\n";
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        const Color &color = (*this)[i][j];
        file << char(255 * clamp(0, 1, color.x));
        file << char(255 * clamp(0, 1, color.y));
        file << char(255 * clamp(0, 1, color.z));
      }
    }
    file.close();
  } else {
    std::cerr << "Failed to open output file " << filename << std::endl;
  }
  return true;
}
