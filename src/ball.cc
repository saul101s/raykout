#include "ball.h"

#include "raylib.h"

namespace Raykout {
void Ball::update(float dt) {
  if (velocity_.isZeroLength()) {
    velocity_ = Vector2{0.0f, -1.0f}.normalized() * config_.max_speed;
  }

  transform.position += velocity_ * dt;
  Vector2 hit_normal;

  float screen_width  = (float)GetScreenWidth();
  float screen_height = (float)GetScreenHeight();

  if (transform.position.x + config_.radius > screen_width) {
    transform.position.x = screen_width - config_.radius;
    hit_normal           = Vector2{-1.0f, 0.0f};  // Right
  } else if (transform.position.x - config_.radius < 0.0f) {
    transform.position.x = config_.radius;
    hit_normal           = Vector2{1.0f, 0.0f};  // Left
  } else if (transform.position.y - config_.radius < 0.0f) {
    transform.position.y = config_.radius;
    hit_normal           = Vector2{0.0f, 1.0f};  // Top
  } else if (transform.position.y + config_.radius > screen_height) {
    transform.position.y = screen_height - config_.radius;
    hit_normal           = Vector2{0.0f, -1.0f};  // Bottom
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