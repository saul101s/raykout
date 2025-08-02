#include "paddle.h"

#include <cmath>

#include "raylib.h"

namespace Raykout {
Paddle::Paddle(const Config& config, const AABB& bounds)
    : config_(config), bounds_(bounds) {}

void Paddle::update(float dt) {
  handleInput(dt);
  updatePosition(dt);
}

void Paddle::attachBall(std::shared_ptr<Ball> ball) {
  ball_ = ball;
  ball_->setVelocity({0.0f, 0.0f});
}

void Paddle::handleInput(float dt) {
  static bool accelerating;

  accelerating = false;

  if (IsKeyDown(KEY_D)) {
    if (velocity_.x < 0.0f) velocity_.x = 0.0f;
    velocity_.x += config_.acceleration * dt;
    accelerating = true;
  }

  if (IsKeyDown(KEY_A)) {
    if (velocity_.x > 0.0f) velocity_.x = 0.0f;
    velocity_.x -= config_.acceleration * dt;
    accelerating = true;
  }

  if (IsKeyPressed(KEY_SPACE) && ball_.get()) {
    ball_->launch(velocity_ / config_.max_speed + Vector2{0.0f, 1.0f});
    ball_ = nullptr;
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
  Vector2 prev_pos = transform.position;
  transform.position += velocity_ * dt;

  if (velocity_.x > 0 && transform.position.x + scaledWidth() / 2.0f > bounds_.max.x) {
    transform.position.x = bounds_.max.x - scaledWidth() / 2.0f;
    velocity_.x          = 0.0f;
  }

  if (velocity_.x < 0 && transform.position.x - scaledWidth() / 2.0f < bounds_.min.x) {
    transform.position.x = bounds_.min.x + scaledWidth() / 2.0f;
    velocity_.x          = 0.0f;
  }

  if (ball_.get())
    ball_->transform.position.x += (transform.position.x - prev_pos.x);
}

float Paddle::scaledWidth() const {
  return config_.width * transform.scale.x;
}

float Paddle::scaledHeight() const {
  return config_.height * transform.scale.y;
}
}  // namespace Raykout
