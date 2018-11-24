#pragma once
#include "math/vector.h"
#include <cinttypes>
#include <iomanip>
#include <ostream>

template <typename T>
class Matrix44 {
public:
  T m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  Matrix44() {}

  Matrix44(T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T mm, T n, T o, T p) {
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
    m[0][3] = d;
    m[1][0] = e;
    m[1][1] = f;
    m[1][2] = g;
    m[1][3] = h;
    m[2][0] = i;
    m[2][1] = j;
    m[2][2] = k;
    m[2][3] = l;
    m[3][0] = mm;
    m[3][1] = n;
    m[3][2] = o;
    m[3][3] = p;
  }
  const T *operator[](uint8_t i) const { return m[i]; }
  T *operator[](uint8_t i) { return m[i]; }

  Matrix44<T> operator*(const Matrix44<T> &rhs) const {
    Matrix44<T> result;
    for (uint8_t i = 0; i < 4; ++i) {
      for (uint8_t j = 0; j < 4; ++j) {
        result[i][j] =
            m[i][0] * rhs[0][j] + m[i][1] * rhs[1][j] + m[i][2] * rhs[2][j] + m[i][3] * rhs[3][j];
      }
    }

    return result;
  }

  // Multiply matrix with a point vector
  template <typename S>
  Vec3<S> multiply_vec(const Vec3<S> &rhs) const {
    Vec3<S> result;
    S a, b, c, w;

    a = rhs[0] * m[0][0] + rhs[1] * m[1][0] + rhs[2] * m[2][0] + m[3][0];
    b = rhs[0] * m[0][1] + rhs[1] * m[1][1] + rhs[2] * m[2][1] + m[3][1];
    c = rhs[0] * m[0][2] + rhs[1] * m[1][2] + rhs[2] * m[2][2] + m[3][2];
    w = rhs[0] * m[0][3] + rhs[1] * m[1][3] + rhs[2] * m[2][3] + m[3][3];

    result.x = a / w;
    result.y = b / w;
    result.z = c / w;
    return result;
  }

  // Multiply matrix with a direction vector (ignores translation)
  template <typename S>
  Vec3<S> multiply_dir(const Vec3<S> &src) const {
    Vec3<S> result;

    result.x = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0];
    result.y = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1];
    result.z = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2];

    return result;
  }

  friend std::ostream &operator<<(std::ostream &s, const Matrix44 &m) {
    std::ios_base::fmtflags oldFlags = s.flags();
    int width = 12;
    s.precision(5);
    s.setf(std::ios_base::fixed);

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i == 0 && j == 0) {
          s << "(";
        } else {
          s << " ";
        }
        s << std::setw(width) << m[i][j];
        if (i == 3 && j == 3) {
          s << ")";
        }
      }
      s << "\n";
    }

    s.flags(oldFlags);
    return s;
  }
};

typedef Matrix44<double> Matrix44f;
