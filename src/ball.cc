#include "ball.h"

#include "raylib.h"

namespace Raykout {
void Ball::update(float dt) {
  if (velocity_.isZeroLength()) {
    velocity_ = Vector2{2.0f, -1.0f}.normalized() * 400.0f * dt;
  }

  transform.position += velocity_;
  Vector2 projectVector;

  if (transform.position.x + radius_ > GetScreenWidth()) {
    projectVector = Vector2{-1.0f, 0.0f};
  } else if (transform.position.x - radius_ < 0.0f) {
    projectVector = Vector2{1.0f, 0.0f};
  } else if (transform.position.y - radius_ < 0.0f) {
    projectVector = Vector2{0.0f, 1.0f};
  } else if (transform.position.y + radius_ > GetScreenHeight()) {
    projectVector = Vector2{0.0f, -1.0f};
  }

  if (!projectVector.isZeroLength()) {
    velocity_         = -velocity_;
    Vector2 projected = velocity_.projectedOnto(projectVector);
    Vector2 diff      = projected - velocity_;
    velocity_ += diff * 2;
  }
}

void Ball::draw() const {
  int x = (int)transform.position.x;
  int y = (int)transform.position.y;

  DrawCircle(x, y, radius_, WHITE);
}
}  // namespace Raykout