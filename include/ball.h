#pragma once

#include <string>

#include "audio_manager.h"
#include "transform2d.h"
#include "renderer.h"
#include "physics.h"

namespace Raykout {
class Ball {
 public:
  struct Config {
    float launch_speed                         = 8.0f;
    float max_speed                            = 15.0f;
    float radius                               = 0.2f;
    SampleHandle sfx_hit_paddle_sample_handle_ = -1;
    SampleHandle sfx_hit_brick_sample_handle_  = -1;
    SampleHandle sfx_hit_wall_sample_handle_   = -1;
  };

  Transform2d transform;

 public:
  Ball(const Config& config, const AABB& bounds);
  Ball()                         = delete;
  ~Ball()                        = default;
  Ball(const Ball& o)            = default;
  Ball& operator=(const Ball& o) = default;

  void update(float dt);

  float radius() const { return config_.radius; }
  void launch(Vector2 direction);
  void onCollision(Vector2 hit_normal, const std::string& tag);

  void setVelocity(Vector2 velocity) {
    velocity_ = velocity;
    if (velocity_.lengthSqr() > config_.max_speed * config_.max_speed)
      velocity_.setLength(config_.max_speed);
  }
  Vector2 velocity() const {
    return velocity_;
  }

  Renderer::PriCircle primitive() const { return {transform.position.x, transform.position.y, config_.radius}; }

  AABB aabb() const {
    return AABB{
        Vector2{transform.position.x - config_.radius, transform.position.y - config_.radius},
        Vector2{transform.position.x + config_.radius, transform.position.y + config_.radius}};
  }

  bool enabled() const { return hp_ > 0; }

 private:
  Config config_;
  Vector2 velocity_;
  AABB bounds_;
  int hp_;
};
}  // namespace Raykout
