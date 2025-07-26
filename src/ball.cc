#include "ball.h"

#include "raylib.h"

namespace Raykout {
Ball::Ball(const Config& config, const AABB& bounds)
    : config_(config), bounds_(bounds) {}

void Ball::update(float dt) {
  if (velocity_.isZeroLength()) {
    velocity_ = Vector2{1.0f, -1.0f}.normalized() * config_.max_speed;
  }

  if (IsKeyPressed(KEY_W)) {
    transform.position.y -= 1.0f;
  }

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
    hit_normal           = Vector2{0.0f, -1.0f};  // Bottom
  } else if (transform.position.y - config_.radius < bounds_.min.y) {
    transform.position.y = bounds_.min.y + config_.radius;
    hit_normal           = Vector2{0.0f, 1.0f};  // Top
  }

  if (!hit_normal.isZeroLength())
    velocity_ = velocity_.reflected(hit_normal);
}

void Ball::draw() const {
  int x = (int)transform.position.x;
  int y = (int)transform.position.y;

  DrawCircle(x, y, config_.radius, WHITE);
}

void Ball::onCollision(Vector2 hit_normal) {
  velocity_.reflect(hit_normal);
}
}  // namespace Raykout