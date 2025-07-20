#pragma once

#include <cmath>

static constexpr float ZERO_EPSILON = 1e-4f;

namespace Raykout {
struct Vector2 {
  union {
    struct {
      float x;
      float y;
    };

    float d[2];
  };

  Vector2() : x(0), y(0) {}
  Vector2(float x, float y) : x(x), y(y) {}
  ~Vector2()                           = default;
  Vector2(const Vector2& o)            = default;
  Vector2& operator=(const Vector2& o) = default;

  float lengthSqr() const { return x * x + y * y; }
  float length() const { return std::sqrt(lengthSqr()); }
  bool isZeroLength() const { return lengthSqr() < ZERO_EPSILON; }

  Vector2 normalized() const {
    if (isZeroLength())
      return *this;
    else
      return *this / length();
  };
  const Vector2& normalize() {
    if (isZeroLength())
      return *this;
    else
      return *this /= length();
  };

  void setLength(float v) {
    *this = normalized() * v;
  }

  Vector2 operator+(const Vector2& o) const { return Vector2{x + o.x, y + o.y}; }
  const Vector2& operator+=(const Vector2& o) {
    x += o.x;
    y += o.y;
    return *this;
  }

  Vector2 operator-(const Vector2& o) const { return Vector2{x - o.x, y - o.y}; }
  const Vector2& operator-=(const Vector2& o) {
    x -= o.x;
    y -= o.y;
    return *this;
  }

  Vector2 operator*(float v) const { return Vector2{x * v, y * v}; }
  const Vector2& operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
  }

  Vector2 operator/(float v) const { return Vector2{x / v, y / v}; }
  const Vector2& operator/=(float v) {
    x /= v;
    y /= v;
    return *this;
  }

  float operator*(const Vector2& o) const { return x * o.x + y * o.y; }
};
}  // namespace Raykout