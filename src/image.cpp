#include "image.h"
#include "math/utils.h"
#include <cinttypes>
#include <fstream>
#include <iomanip>
#include <iostream>

Image::Image(uint16_t xx, uint16_t yy) : x(xx), y(yy) {
  buffer = new Color[x * y];
  for (int i = 0; i < x * y; i++) {
    buffer[i] = {0, 0, 0};
  }
}

Image::~Image() { delete[] buffer; }

const Color *Image::operator[](uint16_t i) const { return &buffer[i * x]; }

Color *Image::operator[](uint16_t i) { return &buffer[i * x]; }

bool Image::to_ppm(const std::string &filename) const {
  std::ofstream file;
  file.open(filename);
  file.setf(std::ios_base::fixed);
  if (file.is_open()) {
    file << "P3\n" << x << " " << y << "\n255\n";
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        const Color &color = (*this)[i][j];
        file << std::setw(4) << int(255 * clamp(0, 1, color.x)) << " ";
        file << std::setw(4) << int(255 * clamp(0, 1, color.y)) << " ";
        file << std::setw(4) << int(255 * clamp(0, 1, color.z)) << " ";
      }
      file << "\n";
    }
    file.close();
  } else {
    std::cerr << "Failed to open output file " << filename << std::endl;
  }
  return true;
}
