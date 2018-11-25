#pragma once
#include <cinttypes>
#include <cmath>
#include <iomanip>
#include <ostream>

template <typename T>
class Vec3 {
public:
  T x, y, z;

  Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
  Vec3(T xx) : x(xx), y(xx), z(xx) {}
  Vec3(const T &xx) : x(xx), y(xx), z(xx) {}
  Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
  Vec3<T> operator+(const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
  Vec3<T> &operator+=(const Vec3<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vec3<T> operator-(const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
  Vec3<T> operator*(const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
  Vec3<T> operator*(const T &r) const { return Vec3<T>(x * r, y * r, z * r); }
  Vec3<T> operator/(const T &r) const {
    if (r != 0) {
      return Vec3<T>(x / r, y / r, z / r);
    } else {
      return *this;
    }
  }
  Vec3<T> &operator/=(const T &r) {
    if (r != 0) {
      x /= r;
      y /= r;
      z /= r;
    }
    return *this;
  }
  const T &operator[](uint8_t i) const { return (&x)[i]; }
  T &operator[](uint8_t i) { return (&x)[i]; }

  T norm() const { return x * x + y * y + z * z; }
  T length() const { return sqrt(norm()); }
  T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }

  Vec3<T> cross(const Vec3<T> &v) const {
    // clang-format off
    return Vec3<T>(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
    // clang-format on
  }

  Vec3<T> &normalize() {
    T len = length();
    if (len > 0) {
      x /= len, y /= len, z /= len;
    }

    return *this;
  }

  friend std::ostream &operator<<(std::ostream &s, const Vec3<T> &v) {
    return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
  }
};

template <typename T>
Vec3<T> operator*(T r, const Vec3<T> &v) {
  return Vec3<T>(r * v.x, r * v.y, r * v.z);
}
template <typename T>
Vec3<T> sqrt(const Vec3<T> &v) {
  Vec3<T> result;
  if (v.x >= 0 && v.y >= 0 && v.z >= 0) {
    result.x = sqrt(v.x);
    result.y = sqrt(v.y);
    result.z = sqrt(v.z);
  }
  return result;
}

typedef Vec3<double> Vec3f;
typedef Vec3f Color;
