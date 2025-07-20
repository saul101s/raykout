#pragma once

#include "transform2d.h"

namespace Raykout {
class Paddle {
 public:
  struct Config {
    float max_speed;
    float acceleration;
    float damping;
  };

  Transform2d transform;

 public:
  Paddle(const Config& config);
  Paddle()                           = delete;
  ~Paddle()                          = default;
  Paddle(const Paddle& o)            = default;
  Paddle& operator=(const Paddle& o) = default;

  void update(float dt);
  void draw() const;

 private:
  void handleInput(float dt);
  void updatePosition(float dt);
  float scaledWidth() const;
  float scaledHeight() const;

 private:
  Vector2 velocity_;
  float max_speed_;
  float acceleration_;
  float damping_;
};
}  // namespace Raykout