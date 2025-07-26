#pragma once

#include "transform2d.h"
#include "renderer.h"
#include "physics.h"

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
  Paddle(const Config& config, const AABB& bounds);
  Paddle()                           = delete;
  ~Paddle()                          = default;
  Paddle(const Paddle& o)            = default;
  Paddle& operator=(const Paddle& o) = default;

  Renderer::PriRectangle primitive() const {
    return {transform.position.x, transform.position.y, scaledWidth(), scaledHeight()};
  }

  AABB aabb() const {
    float half_width  = scaledWidth() / 2.0f;
    float half_height = scaledHeight() / 2.0f;

    return AABB{
        Vector2{transform.position.x - half_width, transform.position.y - half_height},
        Vector2{transform.position.x + half_width, transform.position.y + half_height}};
  }

  void update(float dt);
  void draw() const;
  Vector2 velocity() const { return velocity_; }

 private:
  void handleInput(float dt);
  void updatePosition(float dt);
  float scaledWidth() const;
  float scaledHeight() const;

 private:
  Config config_;
  Vector2 velocity_;
  AABB bounds_;
};
}  // namespace Raykout