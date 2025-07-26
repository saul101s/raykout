#pragma once

#include "transform2d.h"
#include "renderer.h"
#include "physics.h"

namespace Raykout {
class Ball {
 public:
  struct Config {
    float max_speed;
    float radius;
  };

  Transform2d transform;

 public:
  Ball(const Config& config, const AABB& bounds);
  Ball()                         = delete;
  ~Ball()                        = default;
  Ball(const Ball& o)            = default;
  Ball& operator=(const Ball& o) = default;

  void update(float dt);
  void draw() const;
  Vector2 velocity() const { return velocity_; }
  void onCollision(Vector2 hit_normal);

  Renderer::PriCircle primitive() const { return {transform.position.x, transform.position.y, config_.radius}; }

  AABB aabb() const {
    float half_radius = config_.radius / 2.0f;

    return AABB{
        Vector2{transform.position.x - half_radius, transform.position.y - half_radius},
        Vector2{transform.position.x + half_radius, transform.position.y + half_radius}};
  }

 private:
  Config config_;
  Vector2 velocity_;
  AABB bounds_;
};
}  // namespace Raykout