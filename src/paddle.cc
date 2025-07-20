#include "paddle.h"

#include <cmath>

#include "raylib.h"

constexpr int WIDTH  = 60;
constexpr int HEIGHT = 10;

namespace Raykout {
Paddle::Paddle(const Config& config)
    : max_speed_(config.max_speed), acceleration_(config.acceleration), damping_(config.damping) {}

void Paddle::update(float dt) {
  handleInput(dt);
  updatePosition(dt);
}

void Paddle::draw() const {
  int x = (int)transform.position.x;
  int y = (int)transform.position.y;
  DrawRectangle(x, y, (int)scaledWidth(), (int)scaledHeight(), WHITE);
}

void Paddle::handleInput(float dt) {
  static bool accelerating;

  accelerating = false;

  if (IsKeyDown('D')) {
    velocity_.x += acceleration_ * dt;
    accelerating = true;
  }

  if (IsKeyDown('A')) {
    velocity_.x -= acceleration_ * dt;
    accelerating = true;
  }

  if (velocity_.length() > max_speed_) {
    velocity_.setLength(max_speed_);
  }

  if (!accelerating) {
    float speed = velocity_.length();
    speed *= std::powf(damping_, dt);
    velocity_.setLength(speed);
  }
}

void Paddle::updatePosition(float dt) {
  transform.position += velocity_ * dt;

  if (velocity_.x > 0 && transform.position.x + scaledWidth() > (float)GetScreenWidth()) {
    transform.position.x = (float)GetScreenWidth() - scaledWidth();
    velocity_.x          = 0.0f;
  }

  if (velocity_.x < 0 && transform.position.x < 0) {
    transform.position.x = 0;
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
