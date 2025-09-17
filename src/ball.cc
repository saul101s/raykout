#include "ball.h"

namespace Raykout {
Ball::Ball(const Config& config, const AABB& bounds)
    : config_(config), bounds_(bounds), hp_(1) {}

void Ball::update(float dt) {
  transform.position += velocity_ * dt;
  Vector2 hit_normal;

  if (transform.position.x + config_.radius > bounds_.max.x) {
    transform.position.x = bounds_.max.x - config_.radius;
    hit_normal           = Vector2{-1.0f, 0.0f};  // Right
  } else if (transform.position.x - config_.radius < bounds_.min.x) {
    transform.position.x = bounds_.min.x + config_.radius;
    hit_normal           = Vector2{1.0f, 0.0f};  // Left
  } else if (transform.position.y + config_.radius > bounds_.max.y) {
    transform.position.y = bounds_.max.y - config_.radius;
    hit_normal           = Vector2{0.0f, -1.0f};  // Top
  } else if (transform.position.y - config_.radius < bounds_.min.y) {
    hp_                  = 0;
    transform.position.y = bounds_.min.y + config_.radius;
    hit_normal           = Vector2{0.0f, 1.0f};  // Bottom
  }

  if (!hit_normal.isZeroLength()) {
    velocity_.reflect(hit_normal);
    if (config_.sfx_hit_wall_sample_handle_ >= 0)
      AudioManager::Instance().play(config_.sfx_hit_wall_sample_handle_);
  }
}

void Ball::launch(Vector2 direction) {
  if (velocity_.isZeroLength()) {
    velocity_ = direction.normalized() * config_.launch_speed;
  }
}

void Ball::onCollision(Vector2 hit_normal, const std::string& tag) {
  velocity_.reflect(hit_normal);

  float t = 0.0f;

  if (tag.compare("paddle") == 0) {
    t = 0.9f - (velocity_.normalized() * Vector2::Up());
    if (config_.sfx_hit_paddle_sample_handle_ >= 0)
      AudioManager::Instance().play(config_.sfx_hit_paddle_sample_handle_);
  } else {
    t = 0.1f;
    if (config_.sfx_hit_brick_sample_handle_ >= 0)
      AudioManager::Instance().play(config_.sfx_hit_brick_sample_handle_);
  }

  float sd = (config_.max_speed - config_.launch_speed) * t;
  float s  = velocity_.length();
  if (s + sd > config_.max_speed) sd = config_.max_speed - s;
  if (s + sd < config_.launch_speed) sd = config_.launch_speed - s;
  velocity_.setLength(s + sd);
}
}  // namespace Raykout
