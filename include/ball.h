#pragma once

#include "transform2d.h"

namespace Raykout {
class Ball {
 public:
  Transform2d transform;

 public:
  Ball(float radius) : radius_(radius) {}
  Ball()                         = delete;
  ~Ball()                        = default;
  Ball(const Ball& o)            = default;
  Ball& operator=(const Ball& o) = default;

  void update(float dt);
  void draw() const;

 private:
  Vector2 velocity_;
  float radius_;
};
}  // namespace Raykout