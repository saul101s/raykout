#include "paddle.h"

#include <cmath>

#include "raylib.h"

constexpr float WIDTH  = 2.0f;
constexpr float HEIGHT = 0.25f;

namespace Raykout {
Paddle::Paddle(const Config& config, const AABB& bounds)
    : config_(config), bounds_(bounds) {}

void Paddle::update(float dt) {
  handleInput(dt);
  updatePosition(dt);
}

void Paddle::draw() const {
  int x      = (int)transform.position.x;
  int y      = (int)transform.position.y;
  int width  = (int)scaledWidth();
  int height = (int)scaledHeight();
  DrawRectangle(x - width / 2, y - height / 2, width, height, WHITE);
}

void Paddle::handleInput(float dt) {
  static bool accelerating;

  accelerating = false;

  if (IsKeyDown('D')) {
    velocity_.x += config_.acceleration * dt;
    accelerating = true;
  }

  if (IsKeyDown('A')) {
    velocity_.x -= config_.acceleration * dt;
    accelerating = true;
  }

  if (velocity_.length() > config_.max_speed) {
    velocity_.setLength(config_.max_speed);
  }

  if (!accelerating) {
    float speed = velocity_.length();
    speed *= std::powf(config_.damping, dt);
    velocity_.setLength(speed);
  }
}

void Paddle::updatePosition(float dt) {
  transform.position += velocity_ * dt;

  if (velocity_.x > 0 && transform.position.x + scaledWidth() / 2.0f > bounds_.max.x) {
    transform.position.x = bounds_.max.x - scaledWidth() / 2.0f;
    velocity_.x          = 0.0f;
  }

  if (velocity_.x < 0 && transform.position.x - scaledWidth() / 2.0f < bounds_.min.x) {
    transform.position.x = bounds_.min.x + scaledWidth() / 2.0f;
    velocity_.x          = 0.0f;
  }
}

float Paddle::scaledWidth() const {
  return (float)WIDTH * transform.scale.x;
}

float Paddle::scaledHeight() const {
  return (float)HEIGHT * transform.scale.y;
}
}  // namespace Raykout
