#include "paddle.h"

#include <cmath>

#include "raylib.h"

constexpr int WIDTH  = 60;
constexpr int HEIGHT = 10;

namespace Raykout {
Paddle::Paddle(const Config& config)
    : speed_(0.0f), max_speed_(config.max_speed), acceleration_(config.acceleration), damping_(config.damping), x_(0.0f), y_(0.0f) {}

void Paddle::setPosition(float x, float y) {
  x_ = x;
  y_ = y;
}

void Paddle::update(float dt) {
  handleInput(dt);
  updatePosition(dt);
}

void Paddle::draw() {
  DrawRectangle((int)x_, (int)y_, WIDTH, HEIGHT, WHITE);
}

void Paddle::handleInput(float dt) {
  static bool accelerating;

  accelerating = false;

  if (IsKeyDown('D')) {
    speed_ += acceleration_ * dt;
    if (speed_ > max_speed_) {
      speed_ = max_speed_;
    }
    accelerating = true;
  }

  if (IsKeyDown('A')) {
    speed_ -= acceleration_ * dt;
    if (speed_ < -max_speed_) {
      speed_ = -max_speed_;
    }
    accelerating = true;
  }

  if (!accelerating) {
    speed_ *= std::powf(damping_, dt);
  }
}

void Paddle::updatePosition(float dt) {
  x_ += speed_ * dt;

  if (speed_ > 0 && x_ + WIDTH > GetScreenWidth()) {
    x_     = (float)GetScreenWidth() - (float)WIDTH;
    speed_ = 0.0f;
  }

  if (speed_ < 0 && x_ < 0) {
    x_     = 0;
    speed_ = 0.0f;
  }
}
}  // namespace Raykout
