#pragma once
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
  Vec3<T> operator-(const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
  Vec3<T> operator*(const T &r) const { return Vec3<T>(x * r, y * r, z * r); }
  const T &operator[](uint8_t i) const { return (&x)[i]; }
  T &operator[](uint8_t i) { return (&x)[i]; }

  T norm() const { return x * x + y * y + z * z; }
  T length() const { return sqrt(norm()); }
  T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }

  Vec3<T> cross(const Vec3<T> &v) const {
    return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }

  Vec3<T> &normalize() {
    T len = length();
    if (len > 0) {
      T inverseLength = 1 / len;
      x *= inverseLength, y *= inverseLength, z *= inverseLength;
    }

    return *this;
  }

  friend std::ostream &operator<<(std::ostream &s, const Vec3<T> &v) {
    return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
  }
};

typedef Vec3<double> Vec3f;