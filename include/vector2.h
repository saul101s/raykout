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

  Vector2() : x(0.0f), y(0.0f) {}
  Vector2(float x, float y) : x(x), y(y) {}
  ~Vector2()                           = default;
  Vector2(const Vector2& o)            = default;
  Vector2& operator=(const Vector2& o) = default;

  static Vector2 Zero() { return {0.0f, 0.0f}; }
  static Vector2 One() { return {1.0f, 1.0f}; }
  static Vector2 Up() { return {0.0f, 1.0f}; }
  static Vector2 Down() { return {0.0f, -1.0f}; }
  static Vector2 Left() { return {-1.0f, 0.0f}; }
  static Vector2 Right() { return {1.0f, 0.0f}; }

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

  Vector2 projected(const Vector2& q) const {
    // projqP = ((P * Q) / ||Q||^2) * Q
    return q * ((*this * q) / (q * q));
  }

  Vector2 reflected(const Vector2& q) const {
    Vector2 result    = -*this;
    Vector2 projected = result.projected(q);
    Vector2 diff      = projected - result;
    result += diff * 2;
    return result.normalized() * length();
  }

  void reflect(const Vector2& q) {
    *this = this->reflected(q);
  }

  Vector2 halfWay(const Vector2& q) {
    return (*this + q) / 2.0f;
  }

  Vector2 rotated(float angle) {
    Vector2 result;

    float cos = std::cosf(angle);
    float sin = std::sinf(angle);

    result.x = x * cos - y * sin;
    result.y = x * sin + y * cos;

    return result;
  }

  float cos(const Vector2& o) {
    return normalized() * o.normalized();
  }

  float sin(const Vector2& o) {
    /*
      a x b = | i  j  k |
              | 3  2  0 | = -3k -4k = -7k
              | 2 -1  0 |

      | a x b | = |a| * |b| * sin(a,b)
    */

    Vector2 v1 = normalized();
    Vector2 v2 = o.normalized();
    return v1.x * v2.y - v1.y * v2.x;
  }

  Vector2 operator+(const Vector2& o) const { return Vector2{x + o.x, y + o.y}; }
  const Vector2& operator+=(const Vector2& o) {
    x += o.x;
    y += o.y;
    return *this;
  }

  Vector2 operator-() const { return Vector2{-x, -y}; }
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
