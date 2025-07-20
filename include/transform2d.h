#pragma once

#include "vector2.h"

namespace Raykout {
struct Transform2d {
  Vector2 position;
  Vector2 scale;
  float rotation;

  Transform2d() : position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f) {}
  ~Transform2d()                               = default;
  Transform2d(const Transform2d& o)            = default;
  Transform2d& operator=(const Transform2d& o) = default;
};
}  // namespace Raykout