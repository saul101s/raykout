#include "brick.h"

namespace Raykout {

Brick::Brick(const Config& config)
    : config_(config), hp_(1) {}

void Brick::damage(int hp) {
  if (hp < 0) return;

  hp_ -= hp;
  if (hp_ < 0) hp_ = 0;
}

float Brick::scaledWidth() const { return config_.width * transform.scale.x; }
float Brick::scaledHeight() const { return config_.height * transform.scale.y; }
}  // namespace Raykout
